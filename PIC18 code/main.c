//send to esp fixed
//sprint removed

/****this buffer stores data received from ESP****/
#define BUFFER_SIZE 1500
#define REQ_LINE_BUFF_SIZE 70
#define UNKNOWN 0x00
#define NULL 0x00
#define OK 1
#define ERROR 2
#define FAIL 3
#define READY 4
#define READY_TO_WRITE_TCP 5
#define SERVER_MODE 0
#define AP_MODE 1

sbit digital_out_1 at PORTB.B0;
sbit digital_out_2 at PORTB.B1;
sbit digital_out_3 at PORTB.B2;
sbit digital_out_4 at PORTB.B3;

sbit digital_in_1 at PORTB.B4;
sbit digital_in_2 at PORTB.B5;
sbit digital_in_3 at PORTB.B6;
sbit digital_in_4 at PORTB.B7;

sbit esp_reset_n at PORTC.B0;


/******plateform specific*********/
/*
PwmOut analog_out_1(p21);
AnalogIn tempSensor(p20);*/
/*******************************/


//all possible get requests listed here
 const code char get_index[]="GET /index.html";
 const code  char get_root[]="GET / ";
 const code  char get_logo[]="GET /images/logo.jpg";
 const code  char get_style[]="GET /css/style.css";
 const code  char get_dinputs[]={"GET /dinputs.html"};
 const code  char get_anoutputs[]={"GET /anoutputs.html"};
 const code  char get_aninputs[]={"GET /aninputs.html"};
 const code  char get_toggle_digitalOut[]={"GET /digital_outputs/toggle"};
 const code  char get_status_dig_out[]={"GET /digital_outputs/status"};
 const code  char get_status_dig_in[]={"GET /digital_inputs/status"};
 const code  char get_status_analog_output[]= "GET /analog_outputs/status";
 const code  char get_update_analog_output[]= "GET /analog_outputs/update";
 const code  char get_status_analog_inputs[]= "GET /analog_inputs/status";

 char* codetxt_to_ramtxt(const char* ctxt){
  static char txt[70];
  char i;
  for(i =0; txt[i] = ctxt[i]; i++);

  return txt;
}

/*******************All Web pages*****************/
const char logo_jpg[]={
    0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46, 0x49, 0x46, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01,
    0x00, 0x01, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x3B, 0x43, 0x52, 0x45, 0x41, 0x54, 0x4F, 0x52, 0x3A,
    0x20, 0x67, 0x64, 0x2D, 0x6A, 0x70, 0x65, 0x67, 0x20, 0x76, 0x31, 0x2E, 0x30, 0x20, 0x28, 0x75,
    0x73, 0x69, 0x6E, 0x67, 0x20, 0x49, 0x4A, 0x47, 0x20, 0x4A, 0x50, 0x45, 0x47, 0x20, 0x76, 0x38,
    0x30, 0x29, 0x2C, 0x20, 0x71, 0x75, 0x61, 0x6C, 0x69, 0x74, 0x79, 0x20, 0x3D, 0x20, 0x35, 0x30,
    0x0A, 0xFF, 0xDB, 0x00, 0x43, 0x00, 0x10, 0x0B, 0x0C, 0x0E, 0x0C, 0x0A, 0x10, 0x0E, 0x0D, 0x0E,
    0x12, 0x11, 0x10, 0x13, 0x18, 0x28, 0x1A, 0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25, 0x1D, 0x28,
    0x3A, 0x33, 0x3D, 0x3C, 0x39, 0x33, 0x38, 0x37, 0x40, 0x48, 0x5C, 0x4E, 0x40, 0x44, 0x57, 0x45,
    0x37, 0x38, 0x50, 0x6D, 0x51, 0x57, 0x5F, 0x62, 0x67, 0x68, 0x67, 0x3E, 0x4D, 0x71, 0x79, 0x70,
    0x64, 0x78, 0x5C, 0x65, 0x67, 0x63, 0xFF, 0xDB, 0x00, 0x43, 0x01, 0x11, 0x12, 0x12, 0x18, 0x15,
    0x18, 0x2F, 0x1A, 0x1A, 0x2F, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
    0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0xFF, 0xC0, 0x00, 0x11, 0x08,
    0x00, 0x53, 0x00, 0x6E, 0x03, 0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11, 0x01, 0xFF, 0xC4,
    0x00, 0x1F, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF,
    0xC4, 0x00, 0xB5, 0x10, 0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04,
    0x00, 0x00, 0x01, 0x7D, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21, 0x31, 0x41, 0x06,
    0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1, 0x08, 0x23, 0x42, 0xB1, 0xC1,
    0x15, 0x52, 0xD1, 0xF0, 0x24, 0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17, 0x18, 0x19, 0x1A,
    0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45,
    0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65,
    0x66, 0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x83, 0x84, 0x85,
    0x86, 0x87, 0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3,
    0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA,
    0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8,
    0xD9, 0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4,
    0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFF, 0xC4, 0x00, 0x1F, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0xFF, 0xC4, 0x00, 0xB5, 0x11, 0x00, 0x02, 0x01, 0x02,
    0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00, 0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03,
    0x11, 0x04, 0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81,
    0x08, 0x14, 0x42, 0x91, 0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0, 0x15, 0x62, 0x72, 0xD1,
    0x0A, 0x16, 0x24, 0x34, 0xE1, 0x25, 0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26, 0x27, 0x28, 0x29, 0x2A,
    0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54,
    0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x73, 0x74,
    0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x92,
    0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
    0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
    0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xE2, 0xE3, 0xE4, 0xE5,
    0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFF, 0xDA,
    0x00, 0x0C, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3F, 0x00, 0xEF, 0xE8, 0xA2, 0x8A,
    0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2, 0xB2, 0xF5, 0x7D, 0x7A, 0xD3,
    0x4B, 0x52, 0xAC, 0xDE, 0x64, 0xFD, 0xA3, 0x53, 0xFC, 0xFD, 0x29, 0xA4, 0xDB, 0xB2, 0x13, 0x69,
    0x6A, 0xCD, 0x4A, 0x2B, 0x8D, 0x86, 0xE7, 0x54, 0xBF, 0xBC, 0x8A, 0xEA, 0xE2, 0xE5, 0xAD, 0x54,
    0x9F, 0xDC, 0xC6, 0xAA, 0x49, 0x6F, 0xA2, 0xF7, 0x1E, 0xA4, 0xD7, 0x47, 0xA6, 0x6A, 0x91, 0x5E,
    0x97, 0x88, 0xB2, 0x8B, 0x88, 0x8E, 0x1D, 0x54, 0xE4, 0x1F, 0x71, 0xEA, 0x3F, 0x95, 0x36, 0xAD,
    0xA2, 0x62, 0x4E, 0xE5, 0xFA, 0x28, 0xA2, 0xA4, 0xA0, 0xA2, 0x8A, 0x28, 0x00, 0xA2, 0x8A, 0x28,
    0x00, 0xA2, 0x8A, 0x28, 0x00, 0xA6, 0x4B, 0x2C, 0x70, 0x44, 0xD2, 0x4A, 0xEA, 0x88, 0xA3, 0x25,
    0x98, 0xE0, 0x0A, 0xA3, 0xA9, 0x6B, 0x56, 0xD6, 0x0C, 0x22, 0xCF, 0x9B, 0x70, 0xC4, 0x05, 0x89,
    0x7A, 0xFE, 0x3E, 0x95, 0xC3, 0xEB, 0x7A, 0xAC, 0xD7, 0xF3, 0xB1, 0x92, 0xE5, 0x65, 0x8D, 0x78,
    0x55, 0x8F, 0x85, 0x07, 0xBE, 0x3D, 0x7E, 0xB5, 0x71, 0x8D, 0xF7, 0xD0, 0x97, 0x2E, 0xC7, 0x45,
    0xAC, 0x6B, 0x77, 0x93, 0xC8, 0x96, 0xBA, 0x52, 0x73, 0x20, 0xC9, 0x7C, 0x8D, 0xC0, 0x7A, 0xE3,
    0xF8, 0x47, 0xB9, 0xFD, 0x2B, 0x15, 0xA1, 0x8E, 0xC6, 0xD1, 0xAF, 0x23, 0x29, 0xA8, 0x5C, 0xAB,
    0x62, 0x47, 0xCE, 0xE4, 0x84, 0xFA, 0xE3, 0xF8, 0xBE, 0xBD, 0x2A, 0x95, 0x8D, 0xF8, 0x54, 0x65,
    0x95, 0x0B, 0x8C, 0x61, 0x82, 0x1C, 0x17, 0x5E, 0x38, 0x6F, 0xEF, 0x0C, 0x0F, 0x5A, 0x92, 0xC1,
    0x2E, 0x23, 0x9F, 0xCC, 0xB4, 0x78, 0xCB, 0x30, 0x0A, 0x23, 0xE5, 0x84, 0x99, 0xEA, 0x84, 0x63,
    0x9E, 0x3A, 0xD5, 0xA5, 0xA6, 0x8F, 0xFE, 0x09, 0x2F, 0x7D, 0x4D, 0x78, 0xEE, 0x60, 0xBB, 0x84,
    0xBC, 0x2E, 0xEE, 0x19, 0x41, 0x9C, 0x31, 0xDA, 0x73, 0xDF, 0xCC, 0x93, 0xB2, 0xFA, 0x01, 0x4E,
    0x12, 0xC9, 0x27, 0x90, 0x91, 0xCB, 0xE5, 0x7C, 0xC0, 0xC5, 0x20, 0x8F, 0x07, 0xE9, 0x1A, 0x0E,
    0x76, 0xFA, 0x93, 0x59, 0x77, 0x50, 0x5C, 0xE9, 0x92, 0x49, 0x77, 0x60, 0xAD, 0x10, 0x03, 0x17,
    0x16, 0xCE, 0x03, 0x79, 0x79, 0xFD, 0x19, 0x7D, 0x0D, 0x4B, 0x36, 0xA9, 0x64, 0x2D, 0xC4, 0xAB,
    0x34, 0x92, 0x19, 0x14, 0x79, 0x91, 0x8C, 0x89, 0x1D, 0xBB, 0x87, 0x7E, 0xCB, 0xEC, 0x2B, 0x2E,
    0x4E, 0xB1, 0x2E, 0xFD, 0xCE, 0xB7, 0x49, 0xD5, 0xE3, 0xBD, 0x67, 0xB6, 0x95, 0x90, 0x5D, 0x44,
    0x70, 0xC1, 0x4F, 0xCA, 0xF8, 0xEE, 0xBF, 0xE7, 0x8A, 0xD3, 0xAF, 0x36, 0xB5, 0xD6, 0xD9, 0xA5,
    0x09, 0x72, 0xAB, 0x1C, 0x20, 0xE6, 0x23, 0x0A, 0xED, 0x30, 0x1F, 0x55, 0xF6, 0xF5, 0xAE, 0xD3,
    0x49, 0xD5, 0xD6, 0xE9, 0xFE, 0xCD, 0x3B, 0xA7, 0xDA, 0x02, 0xE4, 0x32, 0x9F, 0x96, 0x55, 0xF5,
    0x1F, 0xE1, 0x55, 0x28, 0x35, 0xBA, 0x12, 0x92, 0x66, 0xAD, 0x14, 0x51, 0x50, 0x50, 0x51, 0x45,
    0x14, 0x00, 0xD9, 0x65, 0x8E, 0x18, 0xDA, 0x49, 0x5D, 0x51, 0x14, 0x64, 0xB3, 0x1C, 0x01, 0x5C,
    0x96, 0xB3, 0xE2, 0xB6, 0x90, 0x98, 0x34, 0xDC, 0xAA, 0xF4, 0x32, 0xE3, 0x93, 0xF4, 0x1D, 0xAA,
    0x0F, 0x17, 0xAD, 0xFA, 0xDD, 0x8F, 0x39, 0xD9, 0xAD, 0x98, 0xFE, 0xEC, 0x2F, 0x41, 0xEC, 0x7D,
    0xEB, 0x2A, 0x45, 0x6D, 0x36, 0xE9, 0x0F, 0x91, 0x3A, 0x7C, 0xBF, 0x7D, 0x8E, 0x08, 0x23, 0xEF,
    0x11, 0x8F, 0xCA, 0xB7, 0xA7, 0x18, 0x25, 0xCC, 0xF5, 0x7D, 0x8C, 0xA4, 0xE4, 0xDD, 0x96, 0x85,
    0x73, 0x6F, 0x75, 0x3C, 0x52, 0x5C, 0x2F, 0x21, 0x70, 0xCE, 0xEC, 0x79, 0x00, 0x9C, 0x67, 0x1D,
    0x48, 0xCF, 0x71, 0x54, 0x5D, 0x59, 0x1C, 0xAB, 0x8C, 0x30, 0xEA, 0x2B, 0x4E, 0x0B, 0x88, 0x50,
    0x33, 0x94, 0x90, 0xC2, 0xEF, 0x97, 0x88, 0x67, 0x0A, 0x3A, 0x02, 0x4F, 0x71, 0x92, 0x7E, 0x5E,
    0x3E, 0xB5, 0x4E, 0xE9, 0xA3, 0x90, 0x11, 0x12, 0x10, 0x07, 0x2A, 0x5B, 0x82, 0xBE, 0xBF, 0x87,
    0xB7, 0xEB, 0xEA, 0xE4, 0xA5, 0x51, 0xDC, 0x71, 0xB4, 0x11, 0x5C, 0x12, 0x18, 0x6D, 0xCE, 0xEC,
    0xF1, 0x8E, 0xB5, 0xA7, 0xA2, 0xCD, 0x7F, 0x0E, 0xA6, 0xAD, 0x66, 0x8A, 0x25, 0x1C, 0x3A, 0x12,
    0x30, 0x57, 0xB8, 0xAA, 0x66, 0x29, 0x20, 0xB7, 0x8D, 0xD1, 0x1C, 0x34, 0x8A, 0x59, 0xBE, 0x53,
    0xB8, 0xA8, 0xC6, 0x5B, 0x38, 0xC0, 0x5C, 0xFF, 0x00, 0x2A, 0x8A, 0x37, 0x68, 0xDD, 0x5D, 0x0E,
    0x08, 0xE4, 0x1A, 0xC6, 0xFC, 0xBA, 0x17, 0x6B, 0x9D, 0x2E, 0xB9, 0xAC, 0x2D, 0xF2, 0x96, 0x85,
    0x92, 0x26, 0x41, 0xB5, 0x19, 0x09, 0x2C, 0xD9, 0xFB, 0xCA, 0x78, 0xE9, 0xD3, 0xF1, 0xFC, 0xC7,
    0x2B, 0x82, 0xAD, 0x83, 0x5A, 0xBB, 0xE2, 0xBD, 0x85, 0xA4, 0x05, 0x22, 0x99, 0x07, 0xCD, 0x92,
    0x00, 0x20, 0x0E, 0x00, 0x01, 0x7A, 0xD5, 0xED, 0x27, 0xC3, 0x93, 0xEA, 0x6C, 0xB2, 0x48, 0x0C,
    0x50, 0x0F, 0xE3, 0x3D, 0x4F, 0xD2, 0xBA, 0x69, 0xB8, 0x42, 0x37, 0xB9, 0x94, 0xF9, 0x9B, 0xB1,
    0x93, 0x61, 0x63, 0x3D, 0xF4, 0xC2, 0x2B, 0x78, 0xCB, 0xB1, 0xF4, 0xED, 0x5D, 0xEE, 0x85, 0xE1,
    0xD8, 0x74, 0xC0, 0x25, 0x94, 0x89, 0x2E, 0x3D, 0x7B, 0x2F, 0xD2, 0xB4, 0x74, 0xFD, 0x3A, 0xDB,
    0x4E, 0x84, 0x47, 0x6D, 0x18, 0x5F, 0x56, 0xEE, 0x6A, 0xD5, 0x65, 0x52, 0xAB, 0x96, 0x8B, 0x61,
    0xC6, 0x9A, 0x5A, 0xB0, 0xA2, 0x8A, 0x2B, 0x13, 0x50, 0xA2, 0x8A, 0x28, 0x02, 0x96, 0xB5, 0x03,
    0x5C, 0xE9, 0x57, 0x11, 0xC7, 0x12, 0xCB, 0x21, 0x5C, 0xAA, 0x37, 0x73, 0x5E, 0x7D, 0x0C, 0xD1,
    0xDB, 0x8B, 0x99, 0x0F, 0x9E, 0x51, 0xD3, 0xC9, 0x60, 0x5B, 0xE7, 0x8F, 0x9E, 0x54, 0xFD, 0x71,
    0x8A, 0xF4, 0xEA, 0xE5, 0x75, 0xFD, 0x1A, 0x49, 0xA6, 0xB8, 0xBE, 0x89, 0x8A, 0x3A, 0x10, 0x36,
    0xB0, 0xCA, 0xCA, 0xA7, 0xA8, 0xC7, 0xD4, 0xD0, 0xA5, 0xCA, 0xFC, 0x82, 0xD7, 0x39, 0x56, 0x69,
    0xAD, 0x20, 0xB6, 0x0D, 0x2B, 0xF9, 0x4D, 0xF3, 0x98, 0x8A, 0xF0, 0xBC, 0xE4, 0x7B, 0x1F, 0x5A,
    0x1A, 0x13, 0x72, 0xB7, 0x17, 0x31, 0x31, 0x68, 0xD7, 0x05, 0x89, 0x5D, 0xA4, 0x93, 0xD7, 0x00,
    0x71, 0x80, 0x6A, 0x5B, 0x39, 0x61, 0x5B, 0xBF, 0xB4, 0x4C, 0xAF, 0x2C, 0x70, 0x82, 0x3C, 0xA7,
    0x19, 0xD8, 0xF8, 0xC0, 0x07, 0x3D, 0xAA, 0xB1, 0x91, 0xD6, 0x49, 0x44, 0x72, 0x34, 0x70, 0xB1,
    0x38, 0x50, 0x7B, 0x1E, 0xD5, 0xD5, 0x06, 0xDE, 0xB1, 0x32, 0x95, 0x96, 0xE6, 0x85, 0xBC, 0xCB,
    0xA9, 0x83, 0x05, 0xE0, 0x69, 0x26, 0x6C, 0x13, 0x20, 0x05, 0xE4, 0x98, 0x0E, 0x88, 0xBD, 0x94,
    0x7A, 0xD5, 0x0B, 0xBD, 0x36, 0xED, 0x6F, 0x56, 0xD6, 0x18, 0xC3, 0xDC, 0xBE, 0x4C, 0x89, 0x18,
    0x1B, 0x63, 0x62, 0x7A, 0x0C, 0x7B, 0x63, 0xF5, 0xAD, 0x3D, 0x17, 0x43, 0xBB, 0xD4, 0x1D, 0x5D,
    0x01, 0x86, 0x15, 0x3F, 0xEB, 0x0F, 0x07, 0xF0, 0xAE, 0xE3, 0x4E, 0xD2, 0xED, 0xB4, 0xE8, 0xB6,
    0xC0, 0x9F, 0x37, 0xF1, 0x39, 0xEA, 0x6A, 0x2A, 0xF2, 0x27, 0xA0, 0xE0, 0xE4, 0xD6, 0xA6, 0x07,
    0x87, 0xFC, 0x1F, 0x1D, 0x9E, 0x2E, 0x2F, 0xCF, 0x9B, 0x31, 0xE7, 0x67, 0x61, 0x5D, 0x58, 0x01,
    0x40, 0x00, 0x00, 0x07, 0x40, 0x28, 0xA2, 0xB0, 0x6E, 0xE6, 0x96, 0x0A, 0x28, 0xA2, 0x80, 0x0A,
    0x28, 0xA2, 0x80, 0x0A, 0x28, 0xA2, 0x80, 0x0A, 0x64, 0xD1, 0x2C, 0xD1, 0x34, 0x6D, 0xD0, 0xFA,
    0x53, 0xE8, 0xA0, 0x0E, 0x5B, 0xC4, 0x3A, 0x2B, 0xCD, 0x33, 0xDC, 0xD9, 0x08, 0xD2, 0x58, 0xD0,
    0x33, 0x06, 0x18, 0x59, 0x57, 0xB8, 0x24, 0x7D, 0x29, 0xB6, 0x3E, 0x19, 0x8A, 0x1B, 0x88, 0x25,
    0xBA, 0x50, 0xFE, 0x67, 0x3B, 0x01, 0xC8, 0x5E, 0x3A, 0x67, 0xBD, 0x75, 0x13, 0x46, 0x25, 0x85,
    0xE3, 0x27, 0x1B, 0xD4, 0xAE, 0x7E, 0xB4, 0xA8, 0xBB, 0x51, 0x57, 0xAE, 0x07, 0x5A, 0x13, 0x6B,
    0x44, 0xC1, 0xA4, 0xF7, 0x15, 0x11, 0x51, 0x42, 0xA2, 0x85, 0x51, 0xC0, 0x03, 0xA0, 0xA5, 0xA2,
    0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2,
    0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2,
    0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0x28, 0xA2, 0x8A, 0x00, 0xFF, 0xD9
};
const char notFound_html[]={"Requested page not found!\r\n"};
const char index_html[]={"<!DOCTYPE html>\n<html>\n<head>\n<title>esp</title>\n<script src=https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js></script>\n<link rel=stylesheet type=text/css href=css/style.css>\n<script>$(document).ready(function(){setInterval(\"getDigitalOutputsStatus()\",2000)});function digital_output_toggle(b){var a=\"/digital_outputs/toggle?pin=\"+b+\"&\"+Math.floor(Math.random()*100000);$.ajax({type:\"GET\",dataType:\"text\",url:a,success:function(c){if(c==\"1\"){$(\"#\"+b).html(\"HIGH\")}else{if(c==\"0\"){$(\"#\"+b).html(\"LOW\")}else{alert(\"could not toggle digital output\")}}},timeout:2000})}function getDigitalOutputsStatus(){var b=\"/digital_outputs/status?\"+Math.floor(Math.random()*10000000);$.ajax({type:\"GET\",dataType:\"json\",url:b,success:function(a){if(a.digital_outputs.dout1[\"state\"]==1){$(\"#dout1\").html(\"HIGH\")}else{$(\"#dout1\").html(\"LOW\")}if(a.digital_outputs.dout2[\"state\"]==1){$(\"#dout2\").html(\"HIGH\")}else{$(\"#dout2\").html(\"LOW\")}if(a.digital_outputs.dout3[\"state\"]==1){$(\"#dout3\").html(\"HIGH\")}else{$(\"#dout3\").html(\"LOW\")}if(a.digital_outputs.dout4[\"state\"]==1){$(\"#dout4\").html(\"HIGH\")}else{$(\"#dout4\").html(\"LOW\")}},timeout:2000})};</script>\n</head>\n<body>\n<header>\n<img src=images/logo.jpg alt=logo.jpg>\n<h1>ESP8266 BASED WEBSERVER</h1>\n</header>\n<nav>\n<ul>\n<li><a class=active href=index.html>Digital Outputs</a></li>\n<li><a href=dinputs.html>Digital inputs</a></li>\n<li><a href=anoutputs.html>Analog Outputs</a></li>\n<li><a href=aninputs.html>Analog Inputs</a></li>\n</ul>\n</nav>\n<section>\n<table>\n<tr>\n<th>Digital Ouput</th>\n<th>Status</th>\n<th>Option</th>\n</tr>\n<tr>\n<td>DOut1</td>\n<td id=dout1>waiting..</td>\n<td><button class=button onclick=\"digital_output_toggle('dout1')\">Toggle</button>\n</td>\n</tr>\n<tr>\n<td>DOut2</td>\n<td id=dout2>waiting..</td>\n<td><button class=button onclick=\"digital_output_toggle('dout2')\">Toggle</button>\n</tr>\n<tr>\n<td>DOut3</td>\n<td id=dout3>waiting..</td>\n<td><button class=button onclick=\"digital_output_toggle('dout3')\">Toggle</button>\n</tr>\n<tr>\n<td>DOut4</td>\n<td id=dout4>waiting..</td>\n<td><button class=button onclick=\"digital_output_toggle('dout4')\">Toggle</button>\n</tr>\n</table>\n</section>\n</body>\n</html>\r\n"};
const char dInputs_html[]={"<!DOCTYPE html>\n<html>\n<head>\n<title>esp</title>\n<link rel=stylesheet type=text/css href=css/style.css>\n<script src=https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js></script>\n<script>$(document).ready(function(){setInterval(\"getDigitalInputsStatus()\",2000)});function getDigitalInputsStatus(){var b=\"/digital_inputs/status?\"+Math.floor(Math.random()*10000000);$.ajax({type:\"GET\",dataType:\"json\",url:b,success:function(a){if(a.digital_inputs.din1[\"state\"]==1){$(\"#din1\").html(\"HIGH\")}else{$(\"#din1\").html(\"LOW\")}if(a.digital_inputs.din2[\"state\"]==1){$(\"#din2\").html(\"HIGH\")}else{$(\"#din2\").html(\"LOW\")}if(a.digital_inputs.din3[\"state\"]==1){$(\"#din3\").html(\"HIGH\")}else{$(\"#din3\").html(\"LOW\")}if(a.digital_inputs.din4[\"state\"]==1){$(\"#din4\").html(\"HIGH\")}else{$(\"#din4\").html(\"LOW\")}},timeout:2000})};</script>\n</head>\n<body>\n<header>\n<img src=images/logo.jpg alt=logo.jpg>\n<h1>ESP8266 BASED WEBSERVER</h1>\n</header>\n<nav>\n<ul>\n<li><a href=index.html>Digital Outputs</a></li>\n<li><a class=active href=dinputs.html>Digital inputs</a></li>\n<li><a href=anoutputs.html>Analog Outputs</a></li>\n<li><a href=aninputs.html>Analog Inputs</a></li>\n</ul>\n</nav>\n<section>\n<table id=inputsTable>\n<tr>\n<th>Digital Input</th>\n<th>Status</th>\n</tr>\n<tr>\n<td>DIn1</td>\n<td id=din1>waiting..</td>\n</td>\n</tr>\n<tr>\n<td>DIn2</td>\n<td id=din2>waiting..</td>\n</tr>\n<tr>\n<td>DIn3</td>\n<td id=din3>waiting..</td>\n</tr>\n<tr>\n<td>DIn4</td>\n<td id=din4>waiting..</td>\n</tr>\n</table>\n</section>\n</body>\n</html>\r\n"};
const char anOutputs_html[]={"<!DOCTYPE html><html><head> <title>esp</title> <link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\"> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js\"></script> <script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script> <script> $(document).ready(function() { setInterval(\"getAnalogOutputStatus()\",2000); displayTemp(); }); var voltage_value=0; function displayTemp(){ google.charts.load('current', {'packages':['gauge']}); google.charts.setOnLoadCallback(drawChart); function drawChart() { var data = google.visualization.arrayToDataTable([ ['Label', 'Value'], ['Volts',1.15], ]); var options = { width: 300, height: 250, redFrom:8.0, redTo: 12.0, yellowFrom:4.0, yellowTo: 8.0, greenFrom: 0.0, greenTo: 4.0, min: 0.0, max: 12.0, minorTicks:2.0 }; var chart = new google.visualization.Gauge(document.getElementById('chart_div')); chart.draw(data, options); setInterval(function() { data.setValue(0, 1, voltage_value); chart.draw(data, options); }, 500); } } function getAnalogOutputStatus() { var a = \"analog_outputs/status?\" + Math.floor(Math.random() * 10000000); $.ajax({ type: \"GET\", dataType: \"text\", url: a, success: function(response) { var scaledResponse=parseFloat(response)*12.0; scaledResponse=scaledResponse.toFixed(2); voltage_value=scaledResponse; }, timeout: 2000 }) }; function setNewVoltageLevel(myValue){ document.getElementById(\"vButton\").disabled=true; setTimeout('document.getElementById(\"vButton\").disabled=false;',2000); var scaledVal=parseFloat(myValue)/12.0; scaledVal=scaledVal.toFixed(2); if(isNaN(scaledVal)==false) { var a = \"/analog_outputs/update?value=\"+scaledVal.toString()+'&'+Math.floor(Math.random()*1000); $.ajax({ type: \"GET\", dataType: \"text\", url: a, success: function(response) { var scaledResponse=parseFloat(response)*12.0; scaledResponse=scaledResponse.toFixed(2); voltage_value=scaledResponse; }, timeout: 2000 }) } }; </script></head><body> <header> <img src=\"images/logo.jpg\" alt=\"logo.jpg\"> <h1>ESP8266 BASED WEBSERVER</h1> </header> <nav> <ul> <li><a href=\"index.html\">Digital Outputs</a> </li> <li><a href=\"dinputs.html\">Digital inputs</a> </li> <li><a class=\"active\" href=\"anoutputs.html\">Analog Outputs</a> </li> <li><a href=\"aninputs.html\">Analog Inputs</a> </li> </ul> </nav> <section> <h3>Enter new voltage value and press Update btton</h3> <input type=\"text\" id=\"volts\" maxlength=\"5\" placeholder=\"Voltage..(0.00-12.00)\"> <button class=\"button\" id=\"vButton\" onclick=\"setNewVoltageLevel(document.getElementById('volts').value);\">Update</button> <div id=\"chart_div\" style=\"width: 300px; height: 250px;\"></div> <h1 style=\"color: blue;margin-left: 50px;\">Voltage Level</h1> </section></body></html>\r\n"};
const char anInputs_html[]={"<!DOCTYPE html><html><head> <title>esp</title> <link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\"> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js\"></script> <script> var temperature; $(document).ready(function() { setInterval(\"getTemperatureVale()\",2000); }); function getTemperatureVale() { var a = \"/analog_inputs/status?\" + Math.floor(Math.random() * 10000000); $.ajax({ type: \"GET\", dataType: \"text\", url: a, success: function(response) { var scaledResponse=parseFloat(response)*50.0; scaledResponse=scaledResponse.toFixed(2); $(\"#temp\").html(scaledResponse.toString()+\"&#8451;\"); }, timeout: 2000 }) }; </script></head><body> <header> <img src=\"images/logo.jpg\" alt=\"logo.jpg\"> <h1>ESP8266 BASED WEBSERVER</h1> </header> <nav> <ul> <li><a href=\"index.html\">Digital Outputs</a> </li> <li><a href=\"dinputs.html\">Digital inputs</a> </li> <li><a href=\"anoutputs.html\">Analog Outputs</a> </li> <li><a class=\"active\" href=\"aninputs.html\">Analog Inputs</a> </li> </ul> </nav> <section> <h1 id=\"temp\" style=\"border-style: solid;border-width: 6px;border-color: red; border-radius: 20px;background-color: #aeb5b7; width: 100px;margin-top: 20px;margin-left: 40px;padding: 20px;\">Waiting..</h1> <h2 style=\"margin-left: 25px;color: blue;\">Temperature Value</h2> </section></body></html>\r\n"};
const char style_css[]={"*{padding:0;margin:0}header{background-color:#27ace5}body{font-family:calibri}header h1{text-align:center;font-size:4em;color:#fff;padding:10px}header img{width:110px;margin-top:10px;float:left}ul{list-style-type:none;margin:0;padding:0;overflow:hidden;background-color:#333}li{float:left}li a{display:block;color:#fff;text-align:center;padding:14px 16px;text-decoration:none}li a:hover:not(.active){background-color:#111}.active{background-color:#4CAF50}table{border-collapse:collapse;width:100%}table#inputsTable{border-collapse:collapse;width:70%}th,td{text-align:left;padding:8px}tr:nth-child(even){background-color:#f2f2f2}th{background-color:#4CAF50;color:#fff}section{width:60%;margin:10px}.button{display:inline-block;padding:10px 15px;font-size:15px;cursor:pointer;text-align:center;text-decoration:none;outline:none;color:#fff;background-color:#4CAF50;border:none;border-radius:15px;box-shadow:0 9px #999}.button:hover{background-color:#3e8e41}.button:active{background-color:#3e8e41;box-shadow:0 5px #666;transform:translateY(4px)}input[type=text],select{width:25%;padding:12px 20px;margin:8px 0;display:inline-block;border:1px solid #ccc;border-radius:4px;box-sizing:border-box}\r\n"};


/************global variables************/

char reqLineBuff[REQ_LINE_BUFF_SIZE];
unsigned char reqLineBufIndex=0;
char rxBuff[BUFFER_SIZE];
unsigned int bufferIndexPrimary=0;//primary esp rx buffer index, increments when receive new data
unsigned int bufferIndexForIpdSearch=0;//is used to scan +IPD string from received data
unsigned int bufferIndexForResponseSearch=0;//to be used for reading esp responses like ok,error, fail etc
char serverIp[16]={"------------"};
char apSsid[33];
char apPassword[33];
unsigned char duty=0;
unsigned int adc_reading;
char espMode=SERVER_MODE;
/****************************************/

/***********************************/
char toggleOutput(char* pinName);
/***********************************/
void initializeEspAsServer(void);
void extractQueryFieldValue(char *someString, char* field, char* value);
void processReqLine(char * stringToProcess);
void HandleHttpRequests(void);
void sendRequestedPageToClient(char id, const char* page,unsigned int len);
void sendRequestedPageToClientRam(char id,  char* page,unsigned int len);
void sendMemArrayToEsp(const char*str,unsigned int len);
void sendStringToEsp(const char* str);
char readEspResponse(void);
void readIp(char* ipPtr);
void resetEspRxBuffer(void);
/********************************/
void resetEspRxBuffer(void)
{
    bufferIndexPrimary=0;
}
void interrupt()
{
        if(RC2IF_bit)
        {
            rxBuff[bufferIndexPrimary++]=uart2_read();
            if(bufferIndexPrimary>=BUFFER_SIZE)
                bufferIndexPrimary=0;
        }
}

void main() {
        PWM1_Init(5000);//5khz pwm signal
        PWM1_Set_Duty(duty);
        PWM1_start();
        uart1_init(230400);//connected to uart-usb converter- to use for debug
        delay_ms(100);
        uart2_init(115200);//connected to ESP
        //UART2_WRITE_TEXT("HELLO\r\n");
        delay_ms(500);
        uart1_write_text(codetxt_to_ramtxt("Hello:"));
        TRISB=0xF0;
        esp_reset_n=1;
        TRISC.RC0=0;
        /********CONFIGURE UART2 Interrupt********/
        RC2IE_bit=1;
        RC2IF_bit=0;//clear flag
        PEIE_bit=1;
        GIE_bit=1;//enable global interrupts

        TRISA.B0=1;
        initializeEspAsServer();
        //uart1_write_text("server started at:");
        uart1_write_text(codetxt_to_ramtxt("server ip:"));
        uart1_write_text(serverIp);
        uart1_write_text(codetxt_to_ramtxt("\r\n"));

        resetEspRxBuffer();
        while(1)
        {
            HandleHttpRequests();
        }
}


void readIp(void)
{
//serverIp
    char buffer[100];
    char* ptr;
    char ipIndex=0;

    RC2IE_bit=0;//DISABLE INTERRUPT
    uart2_write_text(codetxt_to_ramtxt("AT+CIFSR\r\n"));
    while(uart2_data_ready()==0);
    uart2_read_text(buffer,"OK",99);
    //uart1_write_text(buffer);
    ptr=strchr(buffer,'\"');
    if(ptr!=NULL)
    {
        ptr++;
        while(*ptr)
        {
            serverIp[ipIndex++]=*ptr++;
            if(*ptr=='\"')
                break;
        }
    }
    RC2IE_bit=1;//ENABLE INTERRUPT
    serverIp[ipIndex]=0x00;
}

void initializeEspAsServer(void)
{
    char responseFromEsp;
    //while(readEspResponse()==UNKNOWN);
    esp_reset_n=0;
    delay_ms(1);
    esp_reset_n=1;

    //uart2_write_text(codetxt_to_ramtxt("AT+RST\r\n"));//ENABLE ECHO
    while(readEspResponse()!=READY);

    uart1_write_text(codetxt_to_ramtxt("ESP Ready!\r\n"));
   // uart2_write_text("AT+UART=230400,8,1,0,0\r\n");
   //while(readEspResponse()!=OK);
    uart2_write_text(codetxt_to_ramtxt("ATE1\r\n"));//ENABLE ECHO
    while(readEspResponse()!=OK);

    uart2_write_text(codetxt_to_ramtxt("AT+CWMODE_CUR=1\r\n"));//
    while(readEspResponse()!=OK);

    uart2_write_text(codetxt_to_ramtxt("AT+CIPMUX=1\r\n"));
    while(readEspResponse()!=OK);

    uart2_write_text(codetxt_to_ramtxt("AT+CIPSERVER=1,80\r\n"));
    while(readEspResponse()!=OK);

    uart2_write_text(codetxt_to_ramtxt("AT+CIPSTO=5\r\n"));
    while(readEspResponse()!=OK);

    uart2_write_text(codetxt_to_ramtxt("AT+CWJAP_CUR=\"Home\",\"myPassword\"\r\n"));
        
    while(1)
    {
        responseFromEsp=readEspResponse();
        delay_ms(100);
        uart1_write('.');
        if(responseFromEsp==OK || responseFromEsp==FAIL)
            break;
    }
    uart1_write_text(codetxt_to_ramtxt("\r\n"));
    if(responseFromEsp==OK)//If connection successfull, check IP
    {
        char someBuf[120];
        char len;
        char espResp;
        readIp();
        uart2_write_text(codetxt_to_ramtxt("AT+CIPSTART=4,\"TCP\",\"api.thingspeak.com\",80\r\n"));
        do{
            espResp=readEspResponse();
        }
        while(espResp==UNKNOWN);

        if(espResp==OK)
        {
			//use your thingspeak channel's Write api key
            strcpy(someBuf,codetxt_to_ramtxt("GET /update.json?api_key=ZAFGRRPMMEMXST4P&field2="));
            strcat(someBuf,serverIp);
            strcat(someBuf,codetxt_to_ramtxt(" HTTP/1.1\r\nHost:"));
            strcat(someBuf,serverIp);
            strcat(someBuf,codetxt_to_ramtxt("\r\n\r\n"));
            len=strlen(someBuf);
            sendRequestedPageToClientRam('4',someBuf,len);           
        }
    }
    else
    {
        uart1_write_text(codetxt_to_ramtxt("Connection failed!\r\n"));
    }
}

/************to be modified according to mcu being used********************/
void sendMemArrayToEsp(const char*str,unsigned int len)
{
    while(len--)
        uart2_write(*str++);
}
  void sendMemArrayToEspVar(char *str,unsigned int len)
{
    while(len--)
        uart2_write(*str++);
}

char toggleOutput(char* pinName)
{
    if(strcmp(pinName,codetxt_to_ramtxt("dout1"))==0) {
        digital_out_1=!digital_out_1;
        return digital_out_1;
    }
     else if(strcmp(pinName,codetxt_to_ramtxt("dout2"))==0) {
        digital_out_2=!digital_out_2;
        return digital_out_2;
    }
     else if(strcmp(pinName,codetxt_to_ramtxt("dout3"))==0) {
        digital_out_3=!digital_out_3;
        return digital_out_3;
    }
     else if(strcmp(pinName,codetxt_to_ramtxt("dout4"))==0) {
        digital_out_4=!digital_out_4;
        return digital_out_4;
    }
     else return 2;
}


void extractQueryFieldValue(char *someString, char* field, char* value)
{
    char* ptr ;
    char *queryStr = strchr(someString, '?');//get query part
    if (queryStr != NULL) {
        queryStr++;//pin=dout1&234234
    }
    ptr=strtok(queryStr,"=&");
    if(ptr!=NULL)
    {
        strcpy(field,ptr);
        ptr=strtok(NULL,"=&");
    }
    if(ptr!=NULL)
        strcpy(value,ptr);
}

void composeDigitalOutStatus(char* str)
{//"{\"digital_outputs\":{\"dout1\":{\"state\":},\"dout2\":{\"state\":},\"dout3\":{\"state\":},\"dout4\":{\"state\":}}}"
    char pinStatus[2]={0x00};
    strcpy(str,codetxt_to_ramtxt("{\"digital_outputs\":{\"dout1\":{\"state\":"));
    pinStatus[0]=digital_out_1+48;
    strcat(str,pinStatus);
    strcat(str,codetxt_to_ramtxt("},\"dout2\":{\"state\":"));
    pinStatus[0]=digital_out_2+48;
    strcat(str,pinStatus);
    strcat(str,codetxt_to_ramtxt("},\"dout3\":{\"state\":"));
    pinStatus[0]=digital_out_3+48;
    strcat(str,pinStatus);
    strcat(str,codetxt_to_ramtxt("},\"dout4\":{\"state\":"));
    pinStatus[0]=digital_out_4+48;
    strcat(str,pinStatus);
    strcat(str,codetxt_to_ramtxt("}}}"));
}

void composeDigitalInStatus(char* str)
{//"{\"digital_outputs\":{\"dout1\":{\"state\":},\"dout2\":{\"state\":},\"dout3\":{\"state\":},\"dout4\":{\"state\":}}}"
        char pinStatus[2]={0x00};
        strcpy(str,codetxt_to_ramtxt("{\"digital_inputs\":{\"din1\":{\"state\":"));
        pinStatus[0]=digital_in_1+48;
        strcat(str,pinStatus);
        strcat(str,codetxt_to_ramtxt("},\"din2\":{\"state\":"));
        pinStatus[0]=digital_in_2+48;
        strcat(str,pinStatus);
        strcat(str,codetxt_to_ramtxt("},\"din3\":{\"state\":"));
        pinStatus[0]=digital_in_3+48;
        strcat(str,pinStatus);
        strcat(str,codetxt_to_ramtxt("},\"din4\":{\"state\":"));
        pinStatus[0]=digital_in_4+48;
        strcat(str,pinStatus);
        strcat(str,codetxt_to_ramtxt("}}}"));
}

void processReqLine(char * stringToProcess)
{
    char idField;
    char* token;
    char field[10],value[10];
    char someBuffer[100];
    char tempPinState[2]={0x00};
    //char token[60];
    //unsigned int ipdLen;
    //sscanf(webdata,"%c,%d:%s", idField, &ipdLen, token);

    token=strtok(stringToProcess,",:");//token=id
    if(token!=NULL)
    {
        idField=*token;
        token=strtok(NULL,",:");//token=length field
    }
    if(token!=NULL)
    {
        //lengthField=atoi(token);
        token=strtok(NULL,",:");//this is get request
    }
    if(token!=NULL)
    {
        if((strncmp(token,codetxt_to_ramtxt(get_index),strlen(codetxt_to_ramtxt(get_index)))==0)||
        (strncmp(token,codetxt_to_ramtxt(get_root),strlen(codetxt_to_ramtxt(get_root)))==0))
        {
            //send requested resource, index.html
            sendRequestedPageToClient(idField,index_html,2160);
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_logo),strlen(codetxt_to_ramtxt(get_logo)))==0)
        {
            sendRequestedPageToClient(idField,logo_jpg,1852);
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_dinputs),strlen(codetxt_to_ramtxt(get_dinputs)))==0)
        {
            sendRequestedPageToClient(idField,dInputs_html,1499);
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_anoutputs),strlen(codetxt_to_ramtxt(get_anoutputs)))==0)
        {
            sendRequestedPageToClient(idField,anOutputs_html,2717);
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_aninputs),strlen(codetxt_to_ramtxt(get_aninputs)))==0)
        {
            sendRequestedPageToClient(idField,anInputs_html,1320);
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_style),strlen(codetxt_to_ramtxt(get_style)))==0)
        {
            sendRequestedPageToClient(idField,style_css,1192);
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_toggle_digitalOut),strlen(codetxt_to_ramtxt(get_toggle_digitalOut)))==0){
            extractQueryFieldValue(token,field,value);
            if(value!=NULL){
                char stateOfPin=toggleOutput(value);
                tempPinState[0]=stateOfPin+48;
                strcpy(someBuffer,tempPinState);
                sendRequestedPageToClientRam(idField,someBuffer,strlen(someBuffer));
            }
        }

        else if(strncmp(token,codetxt_to_ramtxt(get_status_dig_out),strlen(codetxt_to_ramtxt(get_status_dig_out)))==0) { //index page requested?
            composeDigitalOutStatus(someBuffer);
            sendRequestedPageToClientRam(idField,someBuffer,strlen(someBuffer));
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_status_dig_in),strlen(codetxt_to_ramtxt(get_status_dig_in)))==0){
            composeDigitalInStatus(someBuffer);
            sendRequestedPageToClientRam(idField,someBuffer,strlen(someBuffer));
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_status_analog_output),strlen(codetxt_to_ramtxt(get_status_analog_output)))==0) { //index page requested?.

            float reading=duty/255.0;
            char txt[15];
            FloatToStr(reading, txt);
            strcpy(someBuffer,txt);
            sendRequestedPageToClientRam(idField,someBuffer,strlen(someBuffer));
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_update_analog_output),strlen(codetxt_to_ramtxt(get_update_analog_output)))==0) {

            extractQueryFieldValue(token,field,value);
            duty=atof(value)*255;
            pwm1_set_duty(duty);
            strcpy(someBuffer,value);
            sendRequestedPageToClientRam(idField,someBuffer,strlen(someBuffer));
        }
        else if(strncmp(token,codetxt_to_ramtxt(get_status_analog_inputs),strlen(codetxt_to_ramtxt(get_status_analog_inputs)))==0)
        {
            float reading;
            char txt[15];
            adc_reading=ADC_Read(0);
            reading=adc_reading/1023.0;
            FloatToStr(reading, txt);
            strcpy(someBuffer,txt);
            sendRequestedPageToClientRam(idField,someBuffer,strlen(someBuffer));
        }
        else//if requested page not found,
        {
            sendRequestedPageToClient(idField,notFound_html,27);
        }
    }
}


//will be called automatically

void HandleHttpRequests(void){
    char rxByte;
    static char state=0;
    while(bufferIndexForIpdSearch!=bufferIndexPrimary)//that means there is some data
    {
        rxByte=rxBuff[bufferIndexForIpdSearch++];
        uart1_write(rxByte);
        if(bufferIndexForIpdSearch>=BUFFER_SIZE)
            bufferIndexForIpdSearch=0;
        switch(state)
        {
            case 0:
            if(rxByte=='+')
                state=1;
            break;

            case 1:
            if(rxByte=='I')
                state=2;
            else
                state=0;
            break;

            case 2:
            if(rxByte=='P')
                state=3;
            else
                state=0;
            break;

            case 3:
            if(rxByte=='D')
                state=4;
            else
                state=0;
            break;


            case 4:
            if(rxByte==',')
                state=5;
            else
                state=0;
            break;

            case 5:
            if(rxByte!=0x0d)//end of line not found
            {
                reqLineBuff[reqLineBufIndex++]=rxByte;
            }
            else
            {
                reqLineBuff[reqLineBufIndex]=0x00;
                //sendStringToDebugWindow(reqLineBuff);
                bufferIndexForResponseSearch=bufferIndexForIpdSearch;
                processReqLine(reqLineBuff);
                reqLineBufIndex=0;
                state=0;
            }
            break;

            default:
            state=0;
            break;
        }
    }
}

void sendRequestedPageToClientRam(char id,  char* page,unsigned int len)
{
    char atCommandArray[50];
    unsigned int lenOfPacketToTx;
    unsigned int pageToSendAddress=0;
    char tempEspStatus;
    char lenBuf[7];
    char tempStr[2]={0};
    while(len>0)
    {
            if(len>2048){
                len-=2048;
                lenOfPacketToTx=2048;
            }
            else{
                lenOfPacketToTx=len;
                len=0;
            }

        //sprinti(atCommandArray,"AT+CIPSEND=%c,%d\r\n",id,lenOfPacketToTx);
        IntToStr(lenOfPacketToTx, lenBuf);
        Ltrim(lenBuf);
        strcpy(atCommandArray, codetxt_to_ramtxt("AT+CIPSEND="));
        tempStr[0]=id;
        strcat(atCommandArray,tempStr);
        strcat(atCommandArray,",");
        strcat(atCommandArray,lenBuf);
        strcat(atCommandArray,"\r\n");

        bufferIndexForResponseSearch=bufferIndexPrimary;
        uart2_write_text(atCommandArray);

        while(1)
        {
            tempEspStatus=readEspResponse();
            if(tempEspStatus==READY_TO_WRITE_TCP||tempEspStatus==ERROR ||tempEspStatus==FAIL)
                break;
        }
        //now send page
        if(tempEspStatus==READY_TO_WRITE_TCP)
        {
         //   __disable_irq();
            sendMemArrayToEspVar(page+pageToSendAddress,lenOfPacketToTx);
         //   __enable_irq();
            do{
                tempEspStatus=readEspResponse();
            }
            while(tempEspStatus==UNKNOWN);
            if(tempEspStatus!=OK)//link broken, don't send more data to this link.
                break;
            pageToSendAddress+=lenOfPacketToTx;
        }
        else
            break;
    }
    //AT+CIPCLOSE=ID CRLF
    if(tempEspStatus==OK)
    {
        strcpy(atCommandArray,codetxt_to_ramtxt("AT+CIPCLOSE="));
        tempStr[0]=id;
        strcat(atCommandArray,tempStr);
        strcat(atCommandArray,"\r\n");
        uart2_write_text(atCommandArray);
        while(readEspResponse()==UNKNOWN);
    }
}


//to be called for sending some page
void sendRequestedPageToClient(char id, const char* page,unsigned int len)
{
    char atCommandArray[50];
    unsigned int lenOfPacketToTx;
    unsigned int pageToSendAddress=0;
    char tempEspStatus;
    char tempStr[2]={0};
    char lenBuf[7];
    while(len>0)
    {
            if(len>2048){
                len-=2048;
                lenOfPacketToTx=2048;
            }
            else{
                lenOfPacketToTx=len;
                len=0;
            }
        //writing below lines because sprintf didn't work for mikroC
        IntToStr(lenOfPacketToTx, lenBuf);
        Ltrim(lenBuf);
        strcpy(atCommandArray, codetxt_to_ramtxt("AT+CIPSEND="));
        tempStr[0]=id;
        strcat(atCommandArray,tempStr);
        strcat(atCommandArray,",");
        strcat(atCommandArray,lenBuf);
        strcat(atCommandArray,"\r\n");

        bufferIndexForResponseSearch=bufferIndexPrimary;
        uart2_write_text(atCommandArray);
        //__enable_irq();

        while(1)
        {
            tempEspStatus=readEspResponse();
            if(tempEspStatus==READY_TO_WRITE_TCP||tempEspStatus==ERROR ||tempEspStatus==FAIL)
                break;
        }
        //now send page
        if(tempEspStatus==READY_TO_WRITE_TCP)
        {
         //   __disable_irq();
            sendMemArrayToEsp(page+pageToSendAddress,lenOfPacketToTx);
         //   __enable_irq();
            do{
                tempEspStatus=readEspResponse();
            }
            while(tempEspStatus==UNKNOWN);
            if(tempEspStatus!=OK)//link broken, don't send more data to this link.
                break;
            pageToSendAddress+=lenOfPacketToTx;
        }
        else
            break;
    }

     if(tempEspStatus==OK)
    {
        strcpy(atCommandArray,codetxt_to_ramtxt("AT+CIPCLOSE="));
        tempStr[0]=id;
        strcat(atCommandArray,tempStr);
        strcat(atCommandArray,"\r\n");
        uart2_write_text(atCommandArray);
        while(readEspResponse()==UNKNOWN);
    }

    //AT+CIPCLOSE=ID CRLF
   /* if(tempEspStatus==READY_TO_WRITE_TCP)
    {
        sprinti(atCommandArray,"AT+CIPCLOSE=%c\r\n",id);
        uart2_write_text(atCommandArray);
        while(readEspResponse()==UNKNOWN);
    }*/
}

char readEspResponse(void){
    char rxByte;
    char espResponse=UNKNOWN;
    static char state=0;

    while(bufferIndexForResponseSearch!=bufferIndexPrimary)//that means there is some data
    {
        rxByte=rxBuff[bufferIndexForResponseSearch++];
        //uart1_write(rxByte);//send received byte to debug window
        if(bufferIndexForResponseSearch>=BUFFER_SIZE)
            bufferIndexForResponseSearch=0;

        switch(state)
        {
            case 0:
            if(rxByte=='O') //ok
                state=1;
            else if(rxByte=='E')//error
                state=4;
            else if(rxByte=='F')//fail
                state=10;
            else if(rxByte=='r')//ready
                state=15;
            else if(rxByte=='>')
                state=21;
            break;

            case 1://OK
            if(rxByte=='K')
                state=2;
            else
                state=0;
            break;

            case 2:
            if(rxByte==0x0d)
                state=3;
            else state=0;
            break;

            case 3:
            if(rxByte==0x0A)
                espResponse=OK;
            state=0;
            break;

            case 4://ERROR
            if(rxByte=='R')
                state=5;
            else state=0;
            break;

            case 5:
            if(rxByte=='R')
                state=6;
            else state=0;
            break;

            case 6:
            if(rxByte=='O')
                state=7;
            else state=0;
            break;


            case 7:
            if(rxByte=='R')
                state=8;
            else state=0;
            break;

            case 8:
            if(rxByte==0x0d)
                state=9;
            else state=0;
            break;

            case 9:
            if(rxByte==0x0A)
                espResponse=ERROR;
            state=0;
            break;


            case 10://fail
            if(rxByte=='A')
                state=11;
            else state=0;
            break;


            case 11:
            if(rxByte=='I')
                state=12;
            else state=0;
            break;


            case 12:
            if(rxByte=='L')
                state=13;
            else state=0;

            break;

            case 13:
            if(rxByte==0x0d)
                state=14;
            else state=0;
            break;

            case 14:
            if(rxByte==0x0A)
                espResponse=FAIL;
            state=0;
            break;


            case 15://READY
            if(rxByte=='e')
                state=16;
            else state=0;
            break;


            case 16:
            if(rxByte=='a')
                state=17;
            else state=0;
            break;

            case 17:
            if(rxByte=='d')
                state=18;
            else state=0;
            break;

            case 18:
            if(rxByte=='y')
                state=19;
            else  state=0;
            break;

            case 19:
            if(rxByte==0x0d)
                state=20;
            else state=0;
            break;

            case 20:
            if(rxByte==0x0A)
                espResponse=READY;
            state=0;
            break;

            case 21:
            if(rxByte==0x20)
                espResponse=READY_TO_WRITE_TCP;
            state=0;

            default:
            state=0;
            break;
        }
    }
    return espResponse;
}