#include "My_Speex.h"
#include <iostream>


My_Speex::Encode::Encode()
{






    frame_size = 0;
    quality = 5;
    rate = 8000;
    speex_bits_init(&bits_enc);
    enc_state = speex_encoder_init(speex_lib_get_mode(SPEEX_MODEID_WB));
    speex_encoder_ctl(enc_state, SPEEX_SET_QUALITY, &quality);
    speex_encoder_ctl(enc_state, SPEEX_GET_FRAME_SIZE, &frame_size);
    speex_encoder_ctl(enc_state, SPEEX_SET_SAMPLING_RATE, &rate);
    int on = 1;

//    SpeexPreprocessState *preprocess_state = speex_preprocess_state_init(frame_size, sampling_rate);
//    speex_preprocess_ctl(preprocess_state, request, ptr);

//    speex_preprocess_state_destroy(preprocess_state);
    speex_encoder_ctl(enc_state, SPEEX_SET_VAD, &on);
}

My_Speex::Encode::~Encode()
{

    speex_bits_destroy(&bits_enc);
    speex_encoder_destroy(enc_state);
}

int My_Speex::Encode::encode(short *b, char *cbits)
{
    speex_bits_reset(&bits_enc);
    speex_encode_int(enc_state, b, &bits_enc);
  //  speex_encode(enc_state, input, &bits_enc);

//    int size = speex_bits_nbytes(&ebits);
 //    memset(cbits, 0, frame_size );

    nbBytes = speex_bits_write(&bits_enc, cbits, frame_size);
    //printf("%s\n", cbits);
    return (nbBytes);
}

SpeexBits       My_Speex::Encode::getBits_enc()
{
    return (bits_enc);
}

int             My_Speex::Encode::getRate()
{
    return (rate);
}

int             My_Speex::Encode::getFrame_size()
{
    return (frame_size);
}




My_Speex::Decode::Decode()
{
    int enh = 1;

    frame_size = 0;
    rate = 8000;
    dec_state = speex_decoder_init(speex_lib_get_mode(SPEEX_MODEID_WB));
    speex_bits_init(&bits_dec);
    speex_decoder_ctl(dec_state, SPEEX_SET_ENH, &enh);

    speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &frame_size);
    speex_decoder_ctl(dec_state, SPEEX_SET_SAMPLING_RATE, &rate);
    out = new short[(frame_size) * sizeof(short)];
}

My_Speex::Decode::~Decode()
{
    speex_bits_destroy(&bits_dec);
    speex_decoder_destroy(dec_state);
}




short * My_Speex::Decode::decode(char *decode)
{
    memset(out, 0, frame_size);
    speex_bits_read_from(&bits_dec, decode, (int)strlen(decode));
     if (speex_decode_int(dec_state, &bits_dec, out) == -2)
     {
         std::cout << "decode fail chuck" << std::endl;
     }

 //    int i;
 //    std::cout << size << std::endl;
 //    speex_bits_read_from(&bits_dec, cbits, size);
 //    std::cout << "eeeee" << std::endl;
 //    int frame_size = 0;
 //    speex_decoder_ctl(dec_state, SPEEX_GET_FRAME_SIZE, &frame_size);

  //   speex_decode(dec_state, &bits_dec, output);
 //    for (i=0;i<FRAME_SIZE;i++)
 //     out[i]=output[i];
 //    int i;
 //           for (i=0;i<20;i++)
 //              printf("%hu:", out[i]);
     return out;
}


SpeexBits       My_Speex::Decode::getBits_dec()
{
    return (bits_dec);
}

int             My_Speex::Decode::getRate()
{
    return (rate);
}

int             My_Speex::Decode::getFrame_size()
{
    return (frame_size);
}

short           *My_Speex::Decode::getOut()
{
    return (out);
}

//My_Speex::~My_Speex()
//{
//    speex_bits_destroy(&dbits);
//    speex_decoder_destroy(dec_state);
//    speex_bits_destroy(&ebits);
//    speex_encoder_destroy(enc_state);
//}


//My_Speex::My_Speex()
//{
//    quality = 5;
//    speex_bits_init(&ebits);
//    enc_state = speex_encoder_init(speex_lib_get_mode(SPEEX_MODEID_NB));
//    speex_encoder_ctl(enc_state, SPEEX_SET_QUALITY, &quality);
//    speex_bits_init(&dbits);
//     speex_bits_init(&dbits2);
//    dec_state = speex_decoder_init(speex_lib_get_mode(SPEEX_MODEID_NB));
//}

//#include <speex/speex.h>
// #include <stdio.h>

// /*The frame size in hardcoded for this sample code but it doesn�t have to be*/
// #define FRAME_SIZE 160
// int main(int argc, char **argv)
// {
// char *inFile;
// FILE *fin;
// short in[FRAME_SIZE];
// float input[FRAME_SIZE];
// char cbits[200];
// int nbBytes;
// /*Holds the state of the encoder*/
// void *state;
// /*Holds bits so they can be read and written to by the Speex routines*/
// SpeexBits bits;
// int i, tmp;

// /*Create a new encoder state in narrowband mode*/
// state = speex_encoder_init(&speex_nb_mode);

// /*Set the quality to 8 (15 kbps)*/
// tmp=8;
// speex_encoder_ctl(state, SPEEX_SET_QUALITY, &tmp);

// inFile = argv[1];
// fin = fopen(inFile, "r");

// /*Initialization of the structure that holds the bits*/
// speex_bits_init(&bits);
// while (1)
// {
// /*Read a 16 bits/sample audio frame*/
// fread(in, sizeof(short), FRAME_SIZE, fin);
//if (feof(fin))
// break;
// /*Copy the 16 bits values to float so Speex can work on them*/


// for (i=0;i<FRAME_SIZE;i++)
// input[i]=in[i];

// /*Flush all the bits in the struct so we can encode a new frame*/
// speex_bits_reset(&bits);

// /*Encode the frame*/
// speex_encode(state, input, &bits);
// /*Copy the bits to an array of char that can be written*/
// nbBytes = speex_bits_write(&bits, cbits, 200);

// /*Write the size of the frame first. This is what sampledec expects but
// it�s likely to be different in your own application*/
// fwrite(&nbBytes, sizeof(int), 1, stdout);
// /*Write the compressed data*/
//fwrite(cbits, 1, nbBytes, stdout);

// }

// /*Destroy the encoder state*/
// speex_encoder_destroy(state);
// /*Destroy the bit-packing struct*/
// speex_bits_destroy(&bits);
// fclose(fin);
// return 0;
// }




//#include <speex/speex.h>
// #include <stdio.h>

// /*The frame size in hardcoded for this sample code but it doesn�t have to be*/
// #define FRAME_SIZE 160
// int main(int argc, char **argv)
// {
// char *outFile;
//FILE *fout;
// /*Holds the audio that will be written to file (16 bits per sample)*/
// short out[FRAME_SIZE];
// /*Speex handle samples as float, so we need an array of floats*/
// float output[FRAME_SIZE];
// char cbits[200];
// int nbBytes;
// /*Holds the state of the decoder*/
// void *state;
// /*Holds bits so they can be read and written to by the Speex routines*/
// SpeexBits bits;
// int i, tmp;

// /*Create a new decoder state in narrowband mode*/
// state = speex_decoder_init(&speex_nb_mode);

// /*Set the perceptual enhancement on*/
// tmp=1;
//speex_decoder_ctl(state, SPEEX_SET_ENH, &tmp);

// outFile = argv[1];
// fout = fopen(outFile, "w");

// /*Initialization of the structure that holds the bits*/
// speex_bits_init(&bits);
// while (1)
// {
// /*Read the size encoded by sampleenc, this part will likely be
// different in your application*/
// fread(&nbBytes, sizeof(int), 1, stdin);
// fprintf (stderr, "nbBytes: %d\n", nbBytes);
// if (feof(stdin))
// break;

// /*Read the "packet" encoded by sampleenc*/
// fread(cbits, 1, nbBytes, stdin);
// /*Copy the data into the bit-stream struct*/
// speex_bits_read_from(&bits, cbits, nbBytes);

// /*Decode the data*/
// speex_decode(state, &bits, output);

// /*Copy from float to short (16 bits) for output*/
// for (i=0;i<FRAME_SIZE;i++)
// out[i]=output[i];

// /*Write the decoded audio to file*/
// fwrite(out, sizeof(short), FRAME_SIZE, fout);
// }

// /*Destroy the decoder state*/
// speex_decoder_destroy(state);
// /*Destroy the bit-stream truct*/
// speex_bits_destroy(&bits);
//fclose(fout);
// return 0;
// }
