#!/bin/perl


print "=========== BABEL PACKET TOOL BY MINETT_A =================\n";
print "+++++++                                              ++++++\n";
print "+++++++     you need login and password to           ++++++\n";
print "+++++++     register                                 ++++++\n";
print "+++++++     type help to display the help            ++++++\n";
print "+++++++                                              ++++++\n\n";

use IO::Select;
use IO::Socket;
use Data::Dumper;
use Switch;

use constant {
    AUDIO => 0,
    CONNECTION => 3,
    PROXY_FORWARD => 7,
    PROXY_RECEIVED => 8, 
    TEST_CONNECTION => 13,
    CONNECTION_STATUS => 14
};

my @ids = ('AUDIO',
	   'TEXT',
	   'STATUS',
	   'CONNECTION',
	   'REGISTER',
	   'REMOVEACCOUNT',
	   'HANGUP',
	   'PROXY_FORWARD',
	   'PROXY_RECEIVED',
	   'PROXY_DIRECT',
	   'TYPEERROR',
	   'REQUEST_CONNECTION',
	   'CONNECT_TO_ME',
	   'TEST_CONNECTION');


my @print_h = (
    'ONLINE',
    'OFFLINE',
    'BUSY',
    'ONCALL',
    'DISCONNECTED',
    'NEED_REGISTRATION',
    'INVALID_PACKET',
    'OK',
    'FAILED',
    'TCP',
    'UDP'
);

use constant {
    TCP => 9,
    UDP => 10
};

my $id = 0;
my $lastreceived = '';
my $packetId = 1;

die "USAGE $0 [port]" if (!defined($ARGV[0]));
my $ssock = IO::Socket::INET->new( Proto     => 'tcp',
                                  LocalPort => $ARGV[0],
                                  Listen    => SOMAXCONN,
                                  Reuse     => 1);
my $sock = '';

sub interpret_command  #[line]
{
    my ($line) = (@_);

    @ar = split(/ |	/, $line);
    return if ($#ar == -1);
    switch ($ar[0]) {
	case "help" {
	    print "help:\n";
	    print "send [slotid = 0] [data = 'lol'] : send data to host\n";
	    print "sendp [proxy = 'minett_a'] [slotid = 0] [data = 'lol'] : send data to host by proxy\n";
	    print "sendrp [proxy = 'minett_a'] [slotid = 0] [data = 'lol'] : Simulate a PROXY_RECEIVED packet\n";
	    print "dump [file = 'file'] : dump last packet received to file\n";
	    print "test [type = 'tcp'] [port = '1337'] : test connection to port\n";
	    print "cts status(OK = 7/FAILED = 8) ip: connection status\n";
	    print "ctsp [proxy = 'minett_a'] status(OK = 7/FAILED = 8) ip: connection status\n";
	    print "id [id]:set id of next exec\n";
	    print "ctmp [proxy = 'minett_a'] type(TCP = 9/UDP = 10) ip port: connect to me by proxy\n";
	    print "stat [status id]: send status\n";
	    print "\n";
	}
	case "id" {
	    my $id = $ar[1];
	    $packetId = $id;
	    print "Id set to ", $id, "\n";
	}
	case "stat" {
	    my $statusid = $ar[1];
	    my $data = pack("i", $statusid);
	    print $sock generate_packet($slotid, $data, $ar[3]);
	    print "ok, sent status\n";
	}
	case "send" {
	    my $slotid = $ar[1];
	    $" = ' ';
	    my @f = splice(@ar, 0, 2); 
	    my $data = "@ar";
	    $proxy = "none" if ($proxy eq '');
	    $slotid = 0 if ($slotid eq '');
	    $data = "lol" if ($data eq '');
	    $ar[3] = '';
	    print $sock generate_packet($slotid, $data, $ar[3]);
	    print "ok (sent '", $data, "')\n";
	}
	case "sendrp" {
	    my $proxy = $ar[1];
	    my $slotid = $ar[2];
	    $" = ' ';
	    my @f = splice(@ar, 0, 3); 
	    my $data = "@ar";
	    $proxy = "minett_a" if ($proxy eq '');
	    $slotid = 0 if ($slotid eq '');
	    $data = "lol" if ($data eq '');	    
	    $ar[3] = '';
	    print $sock generate_packet(PROXY_RECEIVED, $proxy . "\x00" .
					generate_packet($slotid, $data, $ar[3]), $ar[3]);
	    print "ok (sent by proxy '", $data, "')\n";
	}
	case "ctsp" {
	    my $proxy = $ar[1];
	    my $st  = $ar[2];	    
	    my $h  = $ar[3];	    
	    my $port = $ar[4];	    
	    my @ips = split(/\./, $h);
	    my $data = pack("i", $st);
	    my $sp = pack("S", $port);
	    $ar[4] = '';
	    foreach (@ips) { $data .= pack("C", $_); }
	    $data .= $sp;
	    
	    print $sock generate_packet(PROXY_FORWARD, $proxy . "\x00" .
					generate_packet(CONNECTION_STATUS, $data, $ar[5]), $ar[5]);
	    print "ok (sent by proxy)\n";
	}
	case "ctmp" {
	    my $proxy = $ar[1];
	    my $st  = $ar[2];	    
	    my $h  = $ar[3];	    
	    my @ips = split(/\./, $h);
	    my $data = pack("i", $st);
	    $ar[4] = '';
	    foreach (@ips) { $data .= pack("C", $_); }
	    
	    print $sock generate_packet(PROXY_FORWARD, $proxy . "\x00" .
					generate_packet(CONNECTION_STATUS, $data, $ar[4]), $ar[4]);
	    print "ok (sent by proxy)\n";
	}
	case "sendp" {
	    my $proxy = $ar[1];
	    my $slotid = $ar[2];
	    $" = ' ';
	    my @f = splice(@ar, 0, 3); 
	    my $data = "@ar";
	    $proxy = "minett_a" if ($proxy eq '');
	    $slotid = 0 if ($slotid eq '');
	    $data = "lol" if ($data eq '');	    
	    print $sock generate_packet(PROXY_FORWARD, $proxy . "\x00" .
					generate_packet($slotid, $data));
	    print "ok (sent by proxy '", $data, "')\n";
	}
	case "dump" {
	    my $file  = $ar[1];
	    unlink($file);
	    $file = 'file' if ($file eq '');
	    open(FILE, ">$file") || print "Cannot open file\n";
	    print FILE $lastreceived;
	    close(FILE);
	    print "dump done.\n";
	}
	case "test" {
	    my $proto  = $ar[1];
	    my $port  = $ar[2];  
	    $proto = 'tcp' if ($proto eq '');
#	    $ip = '127.0.0.1' if ($ip eq '');
	    $port = '1337' if ($port eq '');
	    my $c = TCP;
	    $c = UDP if ($proto eq 'udp');
	    my $data = pack("i", $c);
	    $data .= pack("S", $port);
	    print $sock generate_packet(TEST_CONNECTION, $data, $ar[3]);	    
	}
	case "cts" {
	    my $st  = $ar[1];	    
	    my $data = pack("i", $st);
	    print $sock generate_packet(CONNECTION_STATUS, $data, $ar[2]);
	}
	else {
	    print "$ar[0]: Command not found (type help for list)\n";
	}
    }
    $packetId++;
}

sub generate_packet # [slotid] [data]
{
    # [0x7 slotid(1) packetId(2) len(2) checksum(2) data(?)
    my ($slotid, $data, $id) = (@_);
    my $str = '';
    $str .= pack("C", 0x7);
    $str .= pack("C", int($slotid));
    $str .= pack("S", int($packetId));
    $str .= pack("S", int(length($data)));
    $str .= pack("S", 0x4242);
    $str .= pack("S", 0x4242);
    foreach (split(//, $data)) {
	$str .= pack("C", ord($_));
    }
    ++$packetId;
    return ($str);
}

sub parseHeader #pack
{
    my ($pack, $count) = (@_);
    $count = 0 if ($count eq '');
    my @head = split(//, $pack);
    my @data = ();
    foreach (@head)  {
	push(@data, unpack("C", $_));
    }

    return (false, '') if (scalar(@data) < 8);    
    if (!($data[0] eq 0x7))
    {
	print "Invalid packet received begin with " . sprintf("0x%02x", $data[0]),
	" ", sprintf("0x%02x", $data[1]), "\n";	
#	print "Following packet : \n";
#	foreach (@data) {
#	    print sprintf("0x%02x", $_), " ";
#	}
	print "\n";
	for (my $i = 0; $data[$i] != 0x7; $i++) {	    
	}
	return (true, substr($data, $i));
    }
    my $len = unpack("S", substr($pack, 4, 6));
    my $crc = unpack("S", substr($pack, 6, 8));
    my $crcData = unpack("S", substr($pack, 8, 10));
    my $packetId = unpack("S", substr($pack, 2, 4));
    return (false, '') if (length($pack) - 8 < $len);
    print "\n\t Packet received :\n";
    print "\t   Infos : \n";
    print "\t    - slotType : ", $data[1] ,"\t===> ", $ids[$data[1]], "\n";
    print "\t    - packetId : ",  $packetId, "\t(", sprintf("0x%04x", $packetId), ")\n";
    print "\t    - length : ", $len , "\t(", sprintf("0x%04x", $len), ")\n";
    print "\t    - CRC16 : ", $crc, "\t(", sprintf("0x%04x", $crc), ")\n";
    print "\t    - CRC16Data : ", $crcData, "\t(", sprintf("0x%04x", $crc), ")\n";
    if (int($data[1]) == PROXY_FORWARD || int($data[1]) == PROXY_RECEIVED)
    {
	my @login = split("\x00", substr($pack, 10, $len));
	print "\n   PROXY ";
	print " RECEIVED\n" if (int($data[1]) == PROXY_RECEIVED);
	print " FORWARD\n" if (int($data[1]) == PROXY_FORWARD);
	print "      - with login : ", $login[0], "\n";
	parseHeader(substr($pack, 10 + length($login[0]) + 1, $len), $count + 1);
    }
    else {
	print "\t   Data : \n";
	my $dd = substr($pack, 10, $len);
	print $dd;
	printf "\nIn Hex:\n";
	splice(@data, 0, 10);
	foreach (@data) {
	    print sprintf("0x%02x", $_), " ";
	}
	if (length($dd) == 4) {
	    my $r = unpack("i", $dd);
	    print "  =>  Status ", $print_h[int($r)], "" if (!($print_h[int($r)] eq undef));
	}
    }
    print "\n";
    $lastreceived = substr($pack, 0, 10 + $len);
    return (true, substr($pack, $len + 10));
}


my $readBuffer = '';


vec($read_set,fileno(STDIN),1) = 1;
vec($read_set,fileno($ssock),1) = 1;

$| = 1;
print "\n";
while (1)
{    
    ($nfound,$timeleft) =
    select($rout=$read_set, undef, undef, undef);    
    if (vec($rout, fileno(STDIN), 1))
    {
	$line = (<STDIN>);
	chomp($line);
	interpret_command($line);
    }
    if (vec($rout, fileno($ssock), 1))
    {
	print "Client connected\n";
	$sock = $ssock->accept();
	vec($read_set,fileno($sock),1) = 1;
    }
    if (vec($rout, fileno($sock), 1))
    {
	sysread($sock, $line, 1024);
	next   if ($line eq '');
	$readBuffer .= $line;
	my $c = true;
	while ($c == true && length($readBuffer) > 8) {
	    my ($change, $buf) = parseHeader($readBuffer);
	    if ($change == true) {
		$readBuffer = $buf;
	    } else {
		$c = false;
	    }	    
	}
    }
}

