/*************************************************
*                                                *
*  EasyBMP Cross-Platform Windows Bitmap Library * 
*                                                *
*  Author: Paul Macklin                          *
*   email: macklin01@users.sourceforge.net       *
* support: http://easybmp.sourceforge.net        *
*                                                *
*          file: EasyBMP.cpp                     * 
*    date added: 03-31-2006                      *
* date modified: 12-01-2006                      *
*       version: 1.06                            *
*                                                *
*   License: BSD (revised/modified)              *
* Copyright: 2005-6 by the EasyBMP Project       * 
*                                                *
* description: Actual source file                *
*                                                *
*************************************************/

#include "EasyBMP.h"

/* These functions are defined in EasyBMP.h */

bool EasyBMPwarnings = true;

void SetEasyBMPwarningsOff( void )
{ EasyBMPwarnings = false; }
void SetEasyBMPwarningsOn( void )
{ EasyBMPwarnings = true; }
bool GetEasyBMPwarningState( void )
{ return EasyBMPwarnings; }

/* These functions are defined in EasyBMP_DataStructures.h */

int IntPow( int base, int exponent )
{
 int i;
 int output = 1;
 for( i=0 ; i < exponent ; i++ )
 { output *= base; }
 return output;
}

BMFH::BMFH()
{
 bfType = 19778;
 bfReserved1 = 0;
 bfReserved2 = 0;
}

void BMFH::SwitchEndianess( void )
{
 bfType = FlipWORD( bfType );
 bfSize = FlipDWORD( bfSize );
 bfReserved1 = FlipWORD( bfReserved1 );
 bfReserved2 = FlipWORD( bfReserved2 );
 bfOffBits = FlipDWORD( bfOffBits );
 return;
}

BMIH::BMIH()
{
 biPlanes = 1;
 biCompression = 0;
 biXPelsPerMeter = DefaultXPelsPerMeter;  
 biYPelsPerMeter = DefaultYPelsPerMeter;
 biClrUsed = 0;
 biClrImportant = 0;
}

void BMIH::SwitchEndianess( void )
{
 biSize = FlipDWORD( biSize );
 biWidth = FlipDWORD( biWidth );
 biHeight = FlipDWORD( biHeight );
 biPlanes = FlipWORD( biPlanes );
 biBitCount = FlipWORD( biBitCount );
 biCompression = FlipDWORD( biCompression );
 biSizeImage = FlipDWORD( biSizeImage );
 biXPelsPerMeter = FlipDWORD( biXPelsPerMeter );
 biYPelsPerMeter = FlipDWORD( biYPelsPerMeter );
 biClrUsed = FlipDWORD( biClrUsed );
 biClrImportant = FlipDWORD( biClrImportant );
 return;
}

void BMIH::display( void )
{
 using namespace std;
 cout << "biSize: " << (int) biSize << endl
      << "biWidth: " << (int) biWidth << endl
      << "biHeight: " << (int) biHeight << endl
      << "biPlanes: " << (int) biPlanes << endl
      << "biBitCount: " << (int) biBitCount << endl
      << "biCompression: " << (int) biCompression << endl
      << "biSizeImage: " << (int) biSizeImage << endl
      << "biXPelsPerMeter: " << (int) biXPelsPerMeter << endl
      << "biYPelsPerMeter: " << (int) biYPelsPerMeter << endl
      << "biClrUsed: " << (int) biClrUsed << endl
      << "biClrImportant: " << (int) biClrImportant << endl << endl;
}

void BMFH::display( void )
{
 using namespace std;
 cout << "bfType: " << (int) bfType << endl
      << "bfSize: " << (int) bfSize << endl
      << "bfReserved1: " << (int) bfReserved1 << endl
      << "bfReserved2: " << (int) bfReserved2 << endl
      << "bfOffBits: " << (int) bfOffBits << endl << endl;
}

/* These functions are defined in EasyBMP_BMP.h */

RGBApixel BMP::GetPixel( int i, int j ) const
{
 using namespace std;
 bool Warn = false;
 if( i >= Width )
 { i = Width-1; Warn = true; }
 if( i < 0 )
 { i = 0; Warn = true; }
 if( j >= Height )
 { j = Height-1; Warn = true; }
 if( j < 0 )
 { j = 0; Warn = true; }
 if( Warn && EasyBMPwarnings )
 {
  cout << "EasyBMP Warning: Attempted to access non-existent pixel;" << endl
       << "                 Truncating request to fit in the range [0,"
       << Width-1 << "] x [0," << Height-1 << "]." << endl;
 }	
 return Pixels[i][j];
}

bool BMP::SetPixel( int i, int j, RGBApixel NewPixel )
{
 Pixels[i][j] = NewPixel;
 return true;
}


bool BMP::SetColor( int ColorNumber , RGBApixel NewColor )
{
 using namespace std;
 if( BitDepth != 1 && BitDepth != 4 && BitDepth != 8 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Attempted to change color table for a BMP object" << endl
        << "                 that lacks a color table. Ignoring request." << endl;
  }
  return false;
 }
 if( !Colors )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Attempted to set a color, but the color table" << endl
        << "                 is not defined. Ignoring request." << endl; 
  }
  return false; 
 }
 if( ColorNumber >= TellNumberOfColors() )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Requested color number " 
        << ColorNumber << " is outside the allowed" << endl
        << "                 range [0," << TellNumberOfColors()-1 
	    << "]. Ignoring request to set this color." << endl;
  }
  return false;
 }
 Colors[ColorNumber] = NewColor;
 return true;
}

// RGBApixel BMP::GetColor( int ColorNumber ) const
RGBApixel BMP::GetColor( int ColorNumber )
{ 
 RGBApixel Output;
 Output.Red   = 255;
 Output.Green = 255;
 Output.Blue  = 255;
 Output.Alpha = 0;
 
 using namespace std;
 if( BitDepth != 1 && BitDepth != 4 && BitDepth != 8 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Attempted to access color table for a BMP object" << endl
        << "                 that lacks a color table. Ignoring request." << endl;
  }
  return Output;
 }
 if( !Colors )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Requested a color, but the color table" << endl
        << "                 is not defined. Ignoring request." << endl;
  }
  return Output; 
 }
 if( ColorNumber >= TellNumberOfColors() )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Requested color number " 
        << ColorNumber << " is outside the allowed" << endl
        << "                 range [0," << TellNumberOfColors()-1 
	    << "]. Ignoring request to get this color." << endl;
  }
  return Output;
 }
 Output = Colors[ColorNumber];
 return Output;
}

BMP::BMP()
{
 Width = 1;
 Height = 1;
 BitDepth = 24;
 Pixels = new RGBApixel* [Width];
 Pixels[0] = new RGBApixel [Height];
 Colors = NULL;
 
 XPelsPerMeter = 0;
 YPelsPerMeter = 0;
 
 MetaData1 = NULL;
 SizeOfMetaData1 = 0;
 MetaData2 = NULL;
 SizeOfMetaData2 = 0;
}

// BMP::BMP( const BMP& Input )
BMP::BMP( BMP& Input )
{
 // first, make the image empty.

 Width = 1;
 Height = 1;
 BitDepth = 24;
 Pixels = new RGBApixel* [Width];
 Pixels[0] = new RGBApixel [Height];
 Colors = NULL; 
 XPelsPerMeter = 0;
 YPelsPerMeter = 0;
 
 MetaData1 = NULL;
 SizeOfMetaData1 = 0;
 MetaData2 = NULL;
 SizeOfMetaData2 = 0;

 // now, set the correct bit depth
 
 SetBitDepth( Input.TellBitDepth() );
 
 // set the correct pixel size 
 
 SetSize( Input.TellWidth() , Input.TellHeight() );

 // set the DPI information from Input
 
 SetDPI( Input.TellHorizontalDPI() , Input.TellVerticalDPI() );
 
 // if there is a color table, get all the colors

 if( BitDepth == 1 || BitDepth == 4 ||  
     BitDepth == 8 )
 {
  for( int k=0 ; k < TellNumberOfColors() ; k++ )
  {
   SetColor( k, Input.GetColor( k )); 
  }
 }
 
 // get all the pixels 
 
 for( int j=0; j < Height ; j++ )
 {
  for( int i=0; i < Width ; i++ )
  {
   Pixels[i][j] = *Input(i,j);
//   Pixels[i][j] = Input.GetPixel(i,j); // *Input(i,j);
  }
 }
}

BMP::~BMP()
{
 int i;
 for(i=0;i<Width;i++)
 { delete [] Pixels[i]; }
 delete [] Pixels;
 if( Colors )
 { delete [] Colors; }
 
 if( MetaData1 )
 { delete [] MetaData1; }
 if( MetaData2 )
 { delete [] MetaData2; }
} 

RGBApixel* BMP::operator()(int i, int j)
{
 using namespace std;
 bool Warn = false;
 if( i >= Width )
 { i = Width-1; Warn = true; }
 if( i < 0 )
 { i = 0; Warn = true; }
 if( j >= Height )
 { j = Height-1; Warn = true; }
 if( j < 0 )
 { j = 0; Warn = true; }
 if( Warn && EasyBMPwarnings )
 {
  cout << "EasyBMP Warning: Attempted to access non-existent pixel;" << endl
       << "                 Truncating request to fit in the range [0,"
       << Width-1 << "] x [0," << Height-1 << "]." << endl;
 }	
 return &(Pixels[i][j]);
}

// int BMP::TellBitDepth( void ) const
int BMP::TellBitDepth( void )
{ return BitDepth; }

// int BMP::TellHeight( void ) const
int BMP::TellHeight( void )
{ return Height; }

// int BMP::TellWidth( void ) const
int BMP::TellWidth( void )
{ return Width; }

// int BMP::TellNumberOfColors( void ) const
int BMP::TellNumberOfColors( void )
{
 int output = IntPow( 2, BitDepth );
 if( BitDepth == 32 )
 { output = IntPow( 2, 24 ); }
 return output;
}

bool BMP::SetBitDepth( int NewDepth )
{
 using namespace std;
 if( NewDepth != 1 && NewDepth != 4 && 
     NewDepth != 8 && NewDepth != 16 && 
     NewDepth != 24 && NewDepth != 32 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: User attempted to set unsupported bit depth " 
        << NewDepth << "." << endl
        << "                 Bit depth remains unchanged at " 
	    << BitDepth << "." << endl;
  }
  return false;
 }
 
 BitDepth = NewDepth;
 if( Colors )
 { delete [] Colors; }
 int NumberOfColors = IntPow( 2, BitDepth );
 if( BitDepth == 1 || BitDepth == 4 || BitDepth == 8 )
 { Colors = new RGBApixel [NumberOfColors]; }
 else
 { Colors = NULL; } 
 if( BitDepth == 1 || BitDepth == 4 || BitDepth == 8 )
 { CreateStandardColorTable(); }
 
 return true;
}

bool BMP::SetSize(int NewWidth , int NewHeight )
{
 using namespace std;
 if( NewWidth <= 0 || NewHeight <= 0 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: User attempted to set a non-positive width or height." << endl
        << "                 Size remains unchanged at " 
        << Width << " x " << Height << "." << endl;
  }
  return false;
 }

 int i,j; 

 for(i=0;i<Width;i++)
 { delete [] Pixels[i]; }
 delete [] Pixels;

 Width = NewWidth;
 Height = NewHeight;
 Pixels = new RGBApixel* [ Width ]; 
 
 for(i=0; i<Width; i++)
 { Pixels[i] = new RGBApixel [ Height ]; }
 
 for( i=0 ; i < Width ; i++)
 {
  for( j=0 ; j < Height ; j++ )
  {
   Pixels[i][j].Red = 255; 
   Pixels[i][j].Green = 255; 
   Pixels[i][j].Blue = 255; 
   Pixels[i][j].Alpha = 0;    
  }
 }

 return true; 
}

bool BMP::WriteToFile( const char* FileName )
{
 using namespace std;
 if( !EasyBMPcheckDataSize() )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: Data types are wrong size!" << endl
        << "               You may need to mess with EasyBMP_DataTypes.h" << endl
	    << "               to fix these errors, and then recompile." << endl
	    << "               All 32-bit and 64-bit machines should be" << endl
	    << "               supported, however." << endl << endl;
  }
  return false; 
 }
 
 FILE* fp = fopen( FileName, "wb" );
 if( fp == NULL )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: Cannot open file " 
        << FileName << " for output." << endl;
  }
  fclose( fp );
  return false;
 }
  
 // some preliminaries
 
 double dBytesPerPixel = ( (double) BitDepth ) / 8.0;
 double dBytesPerRow = dBytesPerPixel * (Width+0.0);
 dBytesPerRow = ceil(dBytesPerRow);
  
 int BytePaddingPerRow = 4 - ( (int) (dBytesPerRow) )% 4;
 if( BytePaddingPerRow == 4 )
 { BytePaddingPerRow = 0; } 
 
 double dActualBytesPerRow = dBytesPerRow + BytePaddingPerRow;
 
 double dTotalPixelBytes = Height * dActualBytesPerRow;
 
 double dPaletteSize = 0;
 if( BitDepth == 1 || BitDepth == 4 || BitDepth == 8 )
 { dPaletteSize = IntPow(2,BitDepth)*4.0; }

 // leave some room for 16-bit masks 
 if( BitDepth == 16 )
 { dPaletteSize = 3*4; }
 
 double dTotalFileSize = 14 + 40 + dPaletteSize + dTotalPixelBytes;
 
 // write the file header 
 
 BMFH bmfh;
 bmfh.bfSize = (ebmpDWORD) dTotalFileSize; 
 bmfh.bfReserved1 = 0; 
 bmfh.bfReserved2 = 0; 
 bmfh.bfOffBits = (ebmpDWORD) (14+40+dPaletteSize);  
 
 if( IsBigEndian() )
 { bmfh.SwitchEndianess(); }
 
 fwrite( (char*) &(bmfh.bfType) , sizeof(ebmpWORD) , 1 , fp );
 fwrite( (char*) &(bmfh.bfSize) , sizeof(ebmpDWORD) , 1 , fp );
 fwrite( (char*) &(bmfh.bfReserved1) , sizeof(ebmpWORD) , 1 , fp );
 fwrite( (char*) &(bmfh.bfReserved2) , sizeof(ebmpWORD) , 1 , fp );
 fwrite( (char*) &(bmfh.bfOffBits) , sizeof(ebmpDWORD) , 1 , fp );
 
 // write the info header 
 
 BMIH bmih;
 bmih.biSize = 40;
 bmih.biWidth = Width;
 bmih.biHeight = Height;
 bmih.biPlanes = 1;
 bmih.biBitCount = BitDepth;
 bmih.biCompression = 0;
 bmih.biSizeImage = (ebmpDWORD) dTotalPixelBytes;
 if( XPelsPerMeter )
 { bmih.biXPelsPerMeter = XPelsPerMeter; }
 else
 { bmih.biXPelsPerMeter = DefaultXPelsPerMeter; }
 if( YPelsPerMeter )
 { bmih.biYPelsPerMeter = YPelsPerMeter; }
 else
 { bmih.biYPelsPerMeter = DefaultYPelsPerMeter; }

 bmih.biClrUsed = 0;
 bmih.biClrImportant = 0;

 // indicates that we'll be using bit fields for 16-bit files
 if( BitDepth == 16 )
 { bmih.biCompression = 3; }
 
 if( IsBigEndian() )
 { bmih.SwitchEndianess(); }
 
 fwrite( (char*) &(bmih.biSize) , sizeof(ebmpDWORD) , 1 , fp );
 fwrite( (char*) &(bmih.biWidth) , sizeof(ebmpDWORD) , 1 , fp );
 fwrite( (char*) &(bmih.biHeight) , sizeof(ebmpDWORD) , 1 , fp );
 fwrite( (char*) &(bmih.biPlanes) , sizeof(ebmpWORD) , 1 , fp );
 fwrite( (char*) &(bmih.biBitCount) , sizeof(ebmpWORD) , 1 , fp );
 fwrite( (char*) &(bmih.biCompression) , sizeof(ebmpDWORD) , 1 , fp );
 fwrite( (char*) &(bmih.biSizeImage) , sizeof(ebmpDWORD) , 1 , fp );
 fwrite( (char*) &(bmih.biXPelsPerMeter) , sizeof(ebmpDWORD) , 1 , fp );
 fwrite( (char*) &(bmih.biYPelsPerMeter) , sizeof(ebmpDWORD) , 1 , fp ); 
 fwrite( (char*) &(bmih.biClrUsed) , sizeof(ebmpDWORD) , 1 , fp);
 fwrite( (char*) &(bmih.biClrImportant) , sizeof(ebmpDWORD) , 1 , fp);
 
 // write the palette 
 if( BitDepth == 1 || BitDepth == 4 || BitDepth == 8 )
 {
  int NumberOfColors = IntPow(2,BitDepth);
  
  // if there is no palette, create one 
  if( !Colors )
  {
   if( !Colors )
   { Colors = new RGBApixel [NumberOfColors]; }
   CreateStandardColorTable(); 
  }
   
  int n;
  for( n=0 ; n < NumberOfColors ; n++ )
  { fwrite( (char*) &(Colors[n]) , 4 , 1 , fp ); }
 }
 
 // write the pixels 
 int i,j;
 if( BitDepth != 16 )
 {  
  ebmpBYTE* Buffer;
  int BufferSize = (int) ( (Width*BitDepth)/8.0 );
  while( 8*BufferSize < Width*BitDepth )
  { BufferSize++; }
  while( BufferSize % 4 )
  { BufferSize++; }
  
  Buffer = new ebmpBYTE [BufferSize];
  for( j=0 ; j < BufferSize; j++ )
  { Buffer[j] = 0; }
    
  j=Height-1;
  
  while( j > -1 )
  {
   bool Success = false;
   if( BitDepth == 32 )
   { Success = Write32bitRow( Buffer, BufferSize, j ); }
   if( BitDepth == 24 )
   { Success = Write24bitRow( Buffer, BufferSize, j ); }
   if( BitDepth == 8  )
   { Success = Write8bitRow( Buffer, BufferSize, j ); }
   if( BitDepth == 4  )
   { Success = Write4bitRow( Buffer, BufferSize, j ); }
   if( BitDepth == 1  )
   { Success = Write1bitRow( Buffer, BufferSize, j ); }
   if( Success )
   {
    int BytesWritten = (int) fwrite( (char*) Buffer, 1, BufferSize, fp );
    if( BytesWritten != BufferSize )
    { Success = false; }
   }
   if( !Success )
   {
    if( EasyBMPwarnings )
    {
     cout << "EasyBMP Error: Could not write proper amount of data." << endl;
	}
    j = -1; 
   }
   j--; 
  }
  
  delete [] Buffer;
 }
 
 if( BitDepth == 16 )
 {
  // write the bit masks

  ebmpWORD BlueMask = 31;    // bits 12-16
  ebmpWORD GreenMask = 2016; // bits 6-11
  ebmpWORD RedMask = 63488;  // bits 1-5
  ebmpWORD ZeroWORD;
  
  if( IsBigEndian() )
  { RedMask = FlipWORD( RedMask ); }
  fwrite( (char*) &RedMask , 2 , 1 , fp );
  fwrite( (char*) &ZeroWORD , 2 , 1 , fp );

  if( IsBigEndian() )
  { GreenMask = FlipWORD( GreenMask ); }
  fwrite( (char*) &GreenMask , 2 , 1 , fp );
  fwrite( (char*) &ZeroWORD , 2 , 1 , fp );

  if( IsBigEndian() )
  { BlueMask = FlipWORD( BlueMask ); }
  fwrite( (char*) &BlueMask , 2 , 1 , fp );
  fwrite( (char*) &ZeroWORD , 2 , 1 , fp );

  int DataBytes = Width*2;
  int PaddingBytes = ( 4 - DataBytes % 4 ) % 4;
  
  // write the actual pixels
  
  for( j=Height-1 ; j >= 0 ; j-- )
  {
   // write all row pixel data
   i=0;
   int WriteNumber = 0;
   while( WriteNumber < DataBytes )
   {
    ebmpWORD TempWORD;
	
	ebmpWORD RedWORD = (ebmpWORD) ((Pixels[i][j]).Red / 8);
	ebmpWORD GreenWORD = (ebmpWORD) ((Pixels[i][j]).Green / 4);
	ebmpWORD BlueWORD = (ebmpWORD) ((Pixels[i][j]).Blue / 8);
	
    TempWORD = (RedWORD<<11) + (GreenWORD<<5) + BlueWORD;
	if( IsBigEndian() )
	{ TempWORD = FlipWORD( TempWORD ); }
	
    fwrite( (char*) &TempWORD , 2, 1, fp);
    WriteNumber += 2;
	i++;
   }
   // write any necessary row padding
   WriteNumber = 0;
   while( WriteNumber < PaddingBytes )
   {
    ebmpBYTE TempBYTE;
    fwrite( (char*) &TempBYTE , 1, 1, fp);
    WriteNumber++;
   }
  }
  
 }

 fclose(fp);
 return true;
}

bool BMP::ReadFromFile( const char* FileName )
{ 
 using namespace std;
 if( !EasyBMPcheckDataSize() )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: Data types are wrong size!" << endl
        << "               You may need to mess with EasyBMP_DataTypes.h" << endl
	    << "               to fix these errors, and then recompile." << endl
	    << "               All 32-bit and 64-bit machines should be" << endl
	    << "               supported, however." << endl << endl;
  }
  return false; 
 }

 FILE* fp = fopen( FileName, "rb" );
 if( fp == NULL )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: Cannot open file " 
        << FileName << " for input." << endl;
  }
  SetBitDepth(1);
  SetSize(1,1);
  return false;
 }
 
 // read the file header 
 
 BMFH bmfh;
 bool NotCorrupted = true;
 
 NotCorrupted &= SafeFread( (char*) &(bmfh.bfType) , sizeof(ebmpWORD), 1, fp);
 
 bool IsBitmap = false;
 
 if( IsBigEndian() && bmfh.bfType == 16973 )
 { IsBitmap = true; }
 if( !IsBigEndian() && bmfh.bfType == 19778 )
 { IsBitmap = true; }
 
 if( !IsBitmap ) 
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: " << FileName 
        << " is not a Windows BMP file!" << endl; 
  }
  fclose( fp ); 
  return false;
 }

 NotCorrupted &= SafeFread( (char*) &(bmfh.bfSize) , sizeof(ebmpDWORD) , 1, fp); 
 NotCorrupted &= SafeFread( (char*) &(bmfh.bfReserved1) , sizeof(ebmpWORD) , 1, fp);
 NotCorrupted &= SafeFread( (char*) &(bmfh.bfReserved2) , sizeof(ebmpWORD) , 1, fp);
 NotCorrupted &= SafeFread( (char*) &(bmfh.bfOffBits) , sizeof(ebmpDWORD) , 1 , fp);
 
 if( IsBigEndian() ) 
 { bmfh.SwitchEndianess(); }
  
 // read the info header

 BMIH bmih; 
 
 NotCorrupted &= SafeFread( (char*) &(bmih.biSize) , sizeof(ebmpDWORD) , 1 , fp);
 NotCorrupted &= SafeFread( (char*) &(bmih.biWidth) , sizeof(ebmpDWORD) , 1 , fp); 
 NotCorrupted &= SafeFread( (char*) &(bmih.biHeight) , sizeof(ebmpDWORD) , 1 , fp);
 NotCorrupted &= SafeFread( (char*) &(bmih.biPlanes) , sizeof(ebmpWORD) , 1, fp); 
 NotCorrupted &= SafeFread( (char*) &(bmih.biBitCount) , sizeof(ebmpWORD) , 1, fp);

 NotCorrupted &= SafeFread( (char*) &(bmih.biCompression) , sizeof(ebmpDWORD) , 1 , fp);
 NotCorrupted &= SafeFread( (char*) &(bmih.biSizeImage) , sizeof(ebmpDWORD) , 1 , fp);
 NotCorrupted &= SafeFread( (char*) &(bmih.biXPelsPerMeter) , sizeof(ebmpDWORD) , 1 , fp);
 NotCorrupted &= SafeFread( (char*) &(bmih.biYPelsPerMeter) , sizeof(ebmpDWORD) , 1 , fp);
 NotCorrupted &= SafeFread( (char*) &(bmih.biClrUsed) , sizeof(ebmpDWORD) , 1 , fp);
 NotCorrupted &= SafeFread( (char*) &(bmih.biClrImportant) , sizeof(ebmpDWORD) , 1 , fp);
 
 if( IsBigEndian() ) 
 { bmih.SwitchEndianess(); }

 // a safety catch: if any of the header information didn't read properly, abort
 // future idea: check to see if at least most is self-consistent
  
 if( !NotCorrupted )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: " << FileName 
        << " is obviously corrupted." << endl;
  }
  SetSize(1,1);
  SetBitDepth(1);
  fclose(fp);
  return false;
 } 
 
 XPelsPerMeter = bmih.biXPelsPerMeter;
 YPelsPerMeter = bmih.biYPelsPerMeter;
 
 // if bmih.biCompression 1 or 2, then the file is RLE compressed
 
 if( bmih.biCompression == 1 || bmih.biCompression == 2 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: " << FileName << " is (RLE) compressed." << endl
        << "               EasyBMP does not support compression." << endl;
  }
  SetSize(1,1);
  SetBitDepth(1);
  fclose(fp);
  return false; 
 }
 
 // if bmih.biCompression > 3, then something strange is going on 
 // it's probably an OS2 bitmap file.
 
 if( bmih.biCompression > 3 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: " << FileName << " is in an unsupported format." 
        << endl
        << "               (bmih.biCompression = " 
	    << bmih.biCompression << ")" << endl
	    << "               The file is probably an old OS2 bitmap or corrupted." 
	    << endl;
  }		
  SetSize(1,1);
  SetBitDepth(1);
  fclose(fp);
  return false; 
 }
 
 if( bmih.biCompression == 3 && bmih.biBitCount != 16 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: " << FileName 
        << " uses bit fields and is not a" << endl
        << "               16-bit file. This is not supported." << endl;
  }
  SetSize(1,1);
  SetBitDepth(1);
  fclose(fp);
  return false; 
 }

 // set the bit depth
 
 int TempBitDepth = (int) bmih.biBitCount;
 if(    TempBitDepth != 1  && TempBitDepth != 4 
     && TempBitDepth != 8  && TempBitDepth != 16
     && TempBitDepth != 24 && TempBitDepth != 32 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: " << FileName << " has unrecognized bit depth." << endl;
  }
  SetSize(1,1);
  SetBitDepth(1);
  fclose(fp);
  return false;
 }
 SetBitDepth( (int) bmih.biBitCount ); 
 
 // set the size

 if( (int) bmih.biWidth <= 0 || (int) bmih.biHeight <= 0 ) 
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: " << FileName 
        << " has a non-positive width or height." << endl;
  }
  SetSize(1,1);
  SetBitDepth(1);
  fclose(fp);
  return false;
 } 
 SetSize( (int) bmih.biWidth , (int) bmih.biHeight );
  
 // some preliminaries
 
 double dBytesPerPixel = ( (double) BitDepth ) / 8.0;
 double dBytesPerRow = dBytesPerPixel * (Width+0.0);
 dBytesPerRow = ceil(dBytesPerRow);
  
 int BytePaddingPerRow = 4 - ( (int) (dBytesPerRow) )% 4;
 if( BytePaddingPerRow == 4 )
 { BytePaddingPerRow = 0; }  
 
 // if < 16 bits, read the palette
 
 if( BitDepth < 16 )
 {
  // determine the number of colors specified in the 
  // color table
  
  int NumberOfColorsToRead = ((int) bmfh.bfOffBits - 54 )/4;  
  if( NumberOfColorsToRead > IntPow(2,BitDepth) )
  { NumberOfColorsToRead = IntPow(2,BitDepth); }
 
  if( NumberOfColorsToRead < TellNumberOfColors() )
  {
   if( EasyBMPwarnings )
   {
    cout << "EasyBMP Warning: file " << FileName << " has an underspecified" << endl
         << "                 color table. The table will be padded with extra" << endl
	 	 << "                 white (255,255,255,0) entries." << endl;
   }
  }
 
  int n;
  for( n=0; n < NumberOfColorsToRead ; n++ )
  {
   SafeFread( (char*) &(Colors[n]) , 4 , 1 , fp);     
  }
  for( n=NumberOfColorsToRead ; n < TellNumberOfColors() ; n++ )
  {
   RGBApixel WHITE; 
   WHITE.Red = 255;
   WHITE.Green = 255;
   WHITE.Blue = 255;
   WHITE.Alpha = 0;
   SetColor( n , WHITE );
  }
  
  
 }
 
 // skip blank data if bfOffBits so indicates
 
 int BytesToSkip = bmfh.bfOffBits - 54;;
 if( BitDepth < 16 )
 { BytesToSkip -= 4*IntPow(2,BitDepth); }
 if( BitDepth == 16 && bmih.biCompression == 3 )
 { BytesToSkip -= 3*4; }
 if( BytesToSkip < 0 )
 { BytesToSkip = 0; }
 if( BytesToSkip > 0 && BitDepth != 16 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Extra meta data detected in file " << FileName << endl
        << "                 Data will be skipped." << endl;
  }
  ebmpBYTE* TempSkipBYTE;
  TempSkipBYTE = new ebmpBYTE [BytesToSkip];
  SafeFread( (char*) TempSkipBYTE , BytesToSkip , 1 , fp);   
  delete [] TempSkipBYTE;
 } 
  
 // This code reads 1, 4, 8, 24, and 32-bpp files 
 // with a more-efficient buffered technique.

 int i,j;
 if( BitDepth != 16 )
 {
  int BufferSize = (int) ( (Width*BitDepth) / 8.0 );
  while( 8*BufferSize < Width*BitDepth )
  { BufferSize++; }
  while( BufferSize % 4 )
  { BufferSize++; }
  ebmpBYTE* Buffer;
  Buffer = new ebmpBYTE [BufferSize];
  j= Height-1;
  while( j > -1 )
  {
   int BytesRead = (int) fread( (char*) Buffer, 1, BufferSize, fp );
   if( BytesRead < BufferSize )
   {
    j = -1; 
    if( EasyBMPwarnings )
    {
     cout << "EasyBMP Error: Could not read proper amount of data." << endl;
	}
   }
   else
   {
    bool Success = false;
    if( BitDepth == 1  )
	{ Success = Read1bitRow(  Buffer, BufferSize, j ); }
    if( BitDepth == 4  )
	{ Success = Read4bitRow(  Buffer, BufferSize, j ); }
    if( BitDepth == 8  )
	{ Success = Read8bitRow(  Buffer, BufferSize, j ); }
    if( BitDepth == 24 )
	{ Success = Read24bitRow( Buffer, BufferSize, j ); }
	if( BitDepth == 32 )
	{ Success = Read32bitRow( Buffer, BufferSize, j ); }
    if( !Success )
    {
     if( EasyBMPwarnings )
     {
      cout << "EasyBMP Error: Could not read enough pixel data!" << endl;
	 }
	 j = -1;
    }
   }   
   j--;
  }
  delete [] Buffer; 
 }

 if( BitDepth == 16 )
 {
  int DataBytes = Width*2;
  int PaddingBytes = ( 4 - DataBytes % 4 ) % 4;

  // set the default mask
  
  ebmpWORD BlueMask = 31; // bits 12-16
  ebmpWORD GreenMask = 992; // bits 7-11
  ebmpWORD RedMask = 31744; // bits 2-6

  // read the bit fields, if necessary, to 
  // override the default 5-5-5 mask
  
  if( bmih.biCompression != 0 )
  {
   // read the three bit masks

   ebmpWORD TempMaskWORD;
   //ebmpWORD ZeroWORD; // LO CAMBIE YOOOO!
  
   SafeFread( (char*) &RedMask , 2 , 1 , fp );
   if( IsBigEndian() )
   { RedMask = FlipWORD(RedMask); }
   SafeFread( (char*) &TempMaskWORD , 2, 1, fp );
  
   SafeFread( (char*) &GreenMask , 2 , 1 , fp );
   if( IsBigEndian() )
   { GreenMask = FlipWORD(GreenMask); }
   SafeFread( (char*) &TempMaskWORD , 2, 1, fp );

   SafeFread( (char*) &BlueMask , 2 , 1 , fp );
   if( IsBigEndian() )
   { BlueMask = FlipWORD(BlueMask); }
   SafeFread( (char*) &TempMaskWORD , 2, 1, fp );
  }
  
  // read and skip any meta data

  if( BytesToSkip > 0 )
  {
   if( EasyBMPwarnings )
   {
    cout << "EasyBMP Warning: Extra meta data detected in file " 
         << FileName << endl
         << "                 Data will be skipped." << endl;
   }
   ebmpBYTE* TempSkipBYTE;
   TempSkipBYTE = new ebmpBYTE [BytesToSkip];
   SafeFread( (char*) TempSkipBYTE , BytesToSkip , 1 , fp);
   delete [] TempSkipBYTE;   
  } 
  
  // determine the red, green and blue shifts
  
  int GreenShift = 0; 
  ebmpWORD TempShiftWORD = GreenMask;
  while( TempShiftWORD > 31 )
  { TempShiftWORD = TempShiftWORD>>1; GreenShift++; }  
  int BlueShift = 0;
  TempShiftWORD = BlueMask;
  while( TempShiftWORD > 31 )
  { TempShiftWORD = TempShiftWORD>>1; BlueShift++; }  
  int RedShift = 0;  
  TempShiftWORD = RedMask;
  while( TempShiftWORD > 31 )
  { TempShiftWORD = TempShiftWORD>>1; RedShift++; }  
  
  // read the actual pixels
  
  for( j=Height-1 ; j >= 0 ; j-- )
  {
   i=0;
   int ReadNumber = 0;
   while( ReadNumber < DataBytes )
   {
	ebmpWORD TempWORD;
	SafeFread( (char*) &TempWORD , 2 , 1 , fp );
	if( IsBigEndian() )
	{ TempWORD = FlipWORD(TempWORD); }
    ReadNumber += 2;
  
    ebmpWORD Red = RedMask & TempWORD;
    ebmpWORD Green = GreenMask & TempWORD;
    ebmpWORD Blue = BlueMask & TempWORD;
				
	ebmpBYTE BlueBYTE = (ebmpBYTE) 8*(Blue>>BlueShift);
    ebmpBYTE GreenBYTE = (ebmpBYTE) 8*(Green>>GreenShift);
    ebmpBYTE RedBYTE = (ebmpBYTE) 8*(Red>>RedShift);
		
	(Pixels[i][j]).Red = RedBYTE;
	(Pixels[i][j]).Green = GreenBYTE;
	(Pixels[i][j]).Blue = BlueBYTE;
	
	i++;
   }
   ReadNumber = 0;
   while( ReadNumber < PaddingBytes )
   {
    ebmpBYTE TempBYTE;
    SafeFread( (char*) &TempBYTE , 1, 1, fp);
    ReadNumber++;
   }
  }

 }
 
 fclose(fp);
 return true;
}

bool BMP::CreateStandardColorTable( void )
{
 using namespace std;
 if( BitDepth != 1 && BitDepth != 4 && BitDepth != 8 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Attempted to create color table at a bit" << endl
        << "                 depth that does not require a color table." << endl
    	<< "                 Ignoring request." << endl;
  }
  return false;
 }

 if( BitDepth == 1 )
 {
  int i;
  for( i=0 ; i < 2 ; i++ )
  {
   Colors[i].Red = i*255;
   Colors[i].Green = i*255;
   Colors[i].Blue = i*255;
   Colors[i].Alpha = 0;
  } 
  return true;
 } 

 if( BitDepth == 4 )
 {
  int i = 0;
  int j,k,ell;
  
  // simplify the code for the first 8 colors
  for( ell=0 ; ell < 2 ; ell++ )
  {
   for( k=0 ; k < 2 ; k++ )
   {
    for( j=0 ; j < 2 ; j++ )
    {
     Colors[i].Red = j*128; 
	 Colors[i].Green = k*128;
 	 Colors[i].Blue = ell*128;
   	 i++;
    }
   }
  }
 
  // simplify the code for the last 8 colors
  for( ell=0 ; ell < 2 ; ell++ )
  {
   for( k=0 ; k < 2 ; k++ )
   {
    for( j=0 ; j < 2 ; j++ )
    {
     Colors[i].Red = j*255;
     Colors[i].Green = k*255; 
     Colors[i].Blue = ell*255;
	 i++;
    }
   }
  }
 
  // overwrite the duplicate color
  i=8; 
  Colors[i].Red = 192;
  Colors[i].Green = 192;
  Colors[i].Blue = 192;
   
  for( i=0 ; i < 16 ; i++ )
  { Colors[i].Alpha = 0; }
  return true;
 }

 if( BitDepth == 8 )
 {
  int i=0;
  int j,k,ell;
    
  // do an easy loop, which works for all but colors 
  // 0 to 9 and 246 to 255
  for( ell=0 ; ell < 4 ; ell++ ) 
  {
   for( k=0 ; k < 8 ; k++ )
   {
    for( j=0; j < 8 ; j++ )
    {
     Colors[i].Red = j*32; 
     Colors[i].Green = k*32;
     Colors[i].Blue = ell*64;
     Colors[i].Alpha = 0;
     i++;
    }
   }
  } 
   
  // now redo the first 8 colors  
  i=0;
  for( ell=0 ; ell < 2 ; ell++ ) 
  {
   for( k=0 ; k < 2 ; k++ )
   {
    for( j=0; j < 2 ; j++ )
    {
     Colors[i].Red = j*128;
     Colors[i].Green = k*128;
     Colors[i].Blue = ell*128;
     i++;
    }
   }
  } 
 
  // overwrite colors 7, 8, 9
  i=7;
  Colors[i].Red = 192;
  Colors[i].Green = 192;
  Colors[i].Blue = 192;
  i++; // 8
  Colors[i].Red = 192;
  Colors[i].Green = 220;
  Colors[i].Blue = 192;
  i++; // 9
  Colors[i].Red = 166;
  Colors[i].Green = 202;
  Colors[i].Blue = 240;
   
  // overwrite colors 246 to 255 
  i=246;
  Colors[i].Red = 255;
  Colors[i].Green = 251;
  Colors[i].Blue = 240;
  i++; // 247
  Colors[i].Red = 160;
  Colors[i].Green = 160;
  Colors[i].Blue = 164;
  i++; // 248
  Colors[i].Red = 128;
  Colors[i].Green = 128;
  Colors[i].Blue = 128;
  i++; // 249
  Colors[i].Red = 255;
  Colors[i].Green = 0;
  Colors[i].Blue = 0;
  i++; // 250
  Colors[i].Red = 0;
  Colors[i].Green = 255;
  Colors[i].Blue = 0;
  i++; // 251
  Colors[i].Red = 255;
  Colors[i].Green = 255;
  Colors[i].Blue = 0;
  i++; // 252
  Colors[i].Red = 0;
  Colors[i].Green = 0;
  Colors[i].Blue = 255;
  i++; // 253
  Colors[i].Red = 255;
  Colors[i].Green = 0;
  Colors[i].Blue = 255;
  i++; // 254
  Colors[i].Red = 0;
  Colors[i].Green = 255;
  Colors[i].Blue = 255;
  i++; // 255
  Colors[i].Red = 255;
  Colors[i].Green = 255;
  Colors[i].Blue = 255;
  
  return true;
 }
 return true;
}

bool SafeFread( char* buffer, int size, int number, FILE* fp )
{
 using namespace std;
 int ItemsRead;
 if( feof(fp) )
 { return false; }
 ItemsRead = (int) fread( buffer , size , number , fp );
 if( ItemsRead < number )
 { return false; }
 return true;
}

void BMP::SetDPI( int HorizontalDPI, int VerticalDPI )
{
 XPelsPerMeter = (int) ( HorizontalDPI * 39.37007874015748 );
 YPelsPerMeter = (int) (   VerticalDPI * 39.37007874015748 );
}

// int BMP::TellVerticalDPI( void ) const
int BMP::TellVerticalDPI( void )
{
 if( !YPelsPerMeter )
 { YPelsPerMeter = DefaultYPelsPerMeter; }
 return (int) ( YPelsPerMeter / (double) 39.37007874015748 ); 
}

// int BMP::TellHorizontalDPI( void ) const
int BMP::TellHorizontalDPI( void )
{
 if( !XPelsPerMeter )
 { XPelsPerMeter = DefaultXPelsPerMeter; }
 return (int) ( XPelsPerMeter / (double) 39.37007874015748 );
}

/* These functions are defined in EasyBMP_VariousBMPutilities.h */

BMFH GetBMFH( const char* szFileNameIn )
{
 using namespace std;
 BMFH bmfh;

 FILE* fp;
 fp = fopen( szFileNameIn,"rb");
 
 if( !fp  )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: Cannot initialize from file " 
        << szFileNameIn << "." << endl
        << "               File cannot be opened or does not exist." 
	    << endl;
  }
  bmfh.bfType = 0;
  return bmfh;
 } 
 
 SafeFread( (char*) &(bmfh.bfType) , sizeof(ebmpWORD) , 1 , fp );
 SafeFread( (char*) &(bmfh.bfSize) , sizeof(ebmpDWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmfh.bfReserved1) , sizeof(ebmpWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmfh.bfReserved2) , sizeof(ebmpWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmfh.bfOffBits) , sizeof(ebmpDWORD) , 1 , fp ); 
 
 fclose( fp );
 
 if( IsBigEndian() )
 { bmfh.SwitchEndianess(); }

 return bmfh;
}

BMIH GetBMIH( const char* szFileNameIn )
{
 using namespace std;
 BMFH bmfh;
 BMIH bmih;

 FILE* fp;
 fp = fopen( szFileNameIn,"rb");

 if( !fp  )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: Cannot initialize from file " 
        << szFileNameIn << "." << endl
        << "               File cannot be opened or does not exist." 
	    << endl;
  }
  return bmih;
 } 
 
 // read the bmfh, i.e., first 14 bytes (just to get it out of the way);
 
 ebmpBYTE TempBYTE;
 int i;
 for( i = 14 ; i > 0 ; i-- )
 { SafeFread( (char*) &TempBYTE , sizeof(ebmpBYTE) , 1, fp ); }

 // read the bmih 

 SafeFread( (char*) &(bmih.biSize) , sizeof(ebmpDWORD) , 1 , fp );
 SafeFread( (char*) &(bmih.biWidth) , sizeof(ebmpDWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmih.biHeight) , sizeof(ebmpDWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmih.biPlanes) , sizeof(ebmpWORD) , 1 , fp ); 
 
 SafeFread( (char*) &(bmih.biBitCount) , sizeof(ebmpWORD) , 1 , fp );
 SafeFread( (char*) &(bmih.biCompression) , sizeof(ebmpDWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmih.biSizeImage) , sizeof(ebmpDWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmih.biXPelsPerMeter) , sizeof(ebmpDWORD) , 1 , fp ); 
 
 SafeFread( (char*) &(bmih.biYPelsPerMeter) , sizeof(ebmpDWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmih.biClrUsed) , sizeof(ebmpDWORD) , 1 , fp ); 
 SafeFread( (char*) &(bmih.biClrImportant) , sizeof(ebmpDWORD) , 1 , fp ); 
 
 fclose( fp );
 
 if( IsBigEndian() )
 { bmih.SwitchEndianess(); }

 return bmih;
}

void DisplayBitmapInfo( const char* szFileNameIn )
{
 using namespace std;
 FILE* fp;
 fp = fopen( szFileNameIn,"rb");
 
 if( !fp  )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: Cannot initialize from file " 
        << szFileNameIn << "." << endl
        << "               File cannot be opened or does not exist." 
	    << endl;
  }
  return;
 } 
 fclose( fp );

 // don't duplicate work! Just use the functions from above!
 
 BMFH bmfh = GetBMFH(szFileNameIn);
 BMIH bmih = GetBMIH(szFileNameIn);

 cout << "File information for file " << szFileNameIn 
      << ":" << endl << endl;

 cout << "BITMAPFILEHEADER:" << endl
      << "bfType: " << bmfh.bfType << endl
      << "bfSize: " << bmfh.bfSize << endl
      << "bfReserved1: " << bmfh.bfReserved1 << endl
      << "bfReserved2: " << bmfh.bfReserved2 << endl    
      << "bfOffBits: " << bmfh.bfOffBits << endl << endl;

 cout << "BITMAPINFOHEADER:" << endl
      << "biSize: " << bmih.biSize << endl
      << "biWidth: " << bmih.biWidth << endl
      << "biHeight: " << bmih.biHeight << endl
      << "biPlanes: " << bmih.biPlanes << endl
      << "biBitCount: " << bmih.biBitCount << endl
      << "biCompression: " << bmih.biCompression << endl
      << "biSizeImage: " << bmih.biSizeImage << endl
      << "biXPelsPerMeter: " << bmih.biXPelsPerMeter << endl
      << "biYPelsPerMeter: " << bmih.biYPelsPerMeter << endl
      << "biClrUsed: " << bmih.biClrUsed << endl
      << "biClrImportant: " << bmih.biClrImportant << endl << endl;  
 return;
}

int GetBitmapColorDepth( const char* szFileNameIn )
{
 BMIH bmih = GetBMIH( szFileNameIn );
 return (int) bmih.biBitCount;
}

void PixelToPixelCopy( BMP& From, int FromX, int FromY,  
                       BMP& To, int ToX, int ToY)
{
 *To(ToX,ToY) = *From(FromX,FromY);
 return;
}

void PixelToPixelCopyTransparent( BMP& From, int FromX, int FromY,  
                                  BMP& To, int ToX, int ToY,
                                  RGBApixel& Transparent )
{
 if( From(FromX,FromY)->Red != Transparent.Red ||
     From(FromX,FromY)->Green != Transparent.Green ||
     From(FromX,FromY)->Blue != Transparent.Blue )	 
 { *To(ToX,ToY) = *From(FromX,FromY); }
 return;
}

void RangedPixelToPixelCopy( BMP& From, int FromL , int FromR, int FromB, int FromT, 
                             BMP& To, int ToX, int ToY )
{
 // make sure the conventions are followed
 if( FromB < FromT )
 { int Temp = FromT; FromT = FromB; FromB = Temp; }

 // make sure that the copied regions exist in both bitmaps
 if( FromR >= From.TellWidth() )
 { FromR = From.TellWidth()-1; }
 if( FromL < 0 ){ FromL = 0; }

 if( FromB >= From.TellHeight() )
 { FromB = From.TellHeight()-1; }
 if( FromT < 0 ){ FromT = 0; }
 
 if( ToX+(FromR-FromL) >= To.TellWidth() )
 { FromR = To.TellWidth()-1+FromL-ToX; }
 if( ToY+(FromB-FromT) >= To.TellHeight() )
 { FromB = To.TellHeight()-1+FromT-ToY; } 
 
 int i,j;
 for( j=FromT ; j <= FromB ; j++ )
 { 
  for( i=FromL ; i <= FromR ; i++ )
  {
   PixelToPixelCopy( From, i,j,  
                     To, ToX+(i-FromL), ToY+(j-FromT) );
  }
 }

 return;
}

void RangedPixelToPixelCopyTransparent( 
     BMP& From, int FromL , int FromR, int FromB, int FromT, 
     BMP& To, int ToX, int ToY ,
     RGBApixel& Transparent )
{
 // make sure the conventions are followed
 if( FromB < FromT )
 { int Temp = FromT; FromT = FromB; FromB = Temp; }

 // make sure that the copied regions exist in both bitmaps
 if( FromR >= From.TellWidth() )
 { FromR = From.TellWidth()-1; }
 if( FromL < 0 ){ FromL = 0; }

 if( FromB >= From.TellHeight() )
 { FromB = From.TellHeight()-1; }
 if( FromT < 0 ){ FromT = 0; }
 
 if( ToX+(FromR-FromL) >= To.TellWidth() )
 { FromR = To.TellWidth()-1+FromL-ToX; }
 if( ToY+(FromB-FromT) >= To.TellHeight() )
 { FromB = To.TellHeight()-1+FromT-ToY; } 
 
 int i,j;
 for( j=FromT ; j <= FromB ; j++ )
 { 
  for( i=FromL ; i <= FromR ; i++ )
  {
   PixelToPixelCopyTransparent( From, i,j,  
                     To, ToX+(i-FromL), ToY+(j-FromT) , 
                     Transparent);
  }
 }

 return;
}

bool CreateGrayscaleColorTable( BMP& InputImage )
{
 using namespace std;
 int BitDepth = InputImage.TellBitDepth();
 if( BitDepth != 1 && BitDepth != 4 && BitDepth != 8 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Warning: Attempted to create color table at a bit" << endl
        << "                 depth that does not require a color table." << endl
   	    << "                 Ignoring request." << endl;
  }
  return false;
 }
 int i;
 int NumberOfColors = InputImage.TellNumberOfColors();
 
 ebmpBYTE StepSize;
 if( BitDepth != 1 )
 { StepSize = 255/(NumberOfColors-1); }
 else
 { StepSize = 255; }
  
 for( i=0 ; i < NumberOfColors ; i++ )
 {
  ebmpBYTE TempBYTE = i*StepSize;
  RGBApixel TempColor;
  TempColor.Red = TempBYTE;
  TempColor.Green = TempBYTE;
  TempColor.Blue = TempBYTE;
  TempColor.Alpha = 0;
  InputImage.SetColor( i , TempColor );  
 }
 return true;
}

bool BMP::Read32bitRow( ebmpBYTE* Buffer, int BufferSize, int Row )
{ 
 int i;
 if( Width*4 > BufferSize )
 { return false; }
 for( i=0 ; i < Width ; i++ )
 { memcpy( (char*) &(Pixels[i][Row]), (char*) Buffer+4*i, 4 ); }
 return true;
}

bool BMP::Read24bitRow( ebmpBYTE* Buffer, int BufferSize, int Row )
{ 
 int i;
 if( Width*3 > BufferSize )
 { return false; }
 for( i=0 ; i < Width ; i++ )
 { memcpy( (char*) &(Pixels[i][Row]), Buffer+3*i, 3 ); }
 return true;
}

bool BMP::Read8bitRow(  ebmpBYTE* Buffer, int BufferSize, int Row )
{
 int i;
 if( Width > BufferSize )
 { return false; }
 for( i=0 ; i < Width ; i++ )
 {
  int Index = Buffer[i];
  *( this->operator()(i,Row) )= GetColor(Index); 
 }
 return true;
}

bool BMP::Read4bitRow(  ebmpBYTE* Buffer, int BufferSize, int Row )
{
 int Shifts[2] = {4  ,0 };
 int Masks[2]  = {240,15};
 
 int i=0;
 int j;
 int k=0;
 if( Width > 2*BufferSize )
 { return false; }
 while( i < Width )
 {
  j=0;
  while( j < 2 && i < Width )
  {
   int Index = (int) ( (Buffer[k]&Masks[j]) >> Shifts[j]);
   *( this->operator()(i,Row) )= GetColor(Index); 
   i++; j++;   
  }
  k++;
 }
 return true;
}
bool BMP::Read1bitRow(  ebmpBYTE* Buffer, int BufferSize, int Row )
{
 int Shifts[8] = {7  ,6 ,5 ,4 ,3,2,1,0};
 int Masks[8]  = {128,64,32,16,8,4,2,1};
 
 int i=0;
 int j;
 int k=0;
 
 if( Width > 8*BufferSize )
 { return false; }
 while( i < Width )
 {
  j=0;
  while( j < 8 && i < Width )
  {
   int Index = (int) ( (Buffer[k]&Masks[j]) >> Shifts[j]);
   *( this->operator()(i,Row) )= GetColor(Index); 
   i++; j++;   
  }
  k++;
 }
 return true;
}

bool BMP::Write32bitRow( ebmpBYTE* Buffer, int BufferSize, int Row )
{ 
 int i;
 if( Width*4 > BufferSize )
 { return false; }
 for( i=0 ; i < Width ; i++ )
 { memcpy( (char*) Buffer+4*i, (char*) &(Pixels[i][Row]), 4 ); }
 return true;
}

bool BMP::Write24bitRow( ebmpBYTE* Buffer, int BufferSize, int Row )
{ 
 int i;
 if( Width*3 > BufferSize )
 { return false; }
 for( i=0 ; i < Width ; i++ )
 { memcpy( (char*) Buffer+3*i,  (char*) &(Pixels[i][Row]), 3 ); }
 return true;
}

bool BMP::Write8bitRow(  ebmpBYTE* Buffer, int BufferSize, int Row )
{
 int i;
 if( Width > BufferSize )
 { return false; }
 for( i=0 ; i < Width ; i++ )
 { Buffer[i] = FindClosestColor( Pixels[i][Row] ); }
 return true;
}

bool BMP::Write4bitRow(  ebmpBYTE* Buffer, int BufferSize, int Row )
{ 
 int PositionWeights[2]  = {16,1};
 
 int i=0;
 int j;
 int k=0;
 if( Width > 2*BufferSize )
 { return false; }
 while( i < Width )
 {
  j=0;
  int Index = 0;
  while( j < 2 && i < Width )
  {
   Index += ( PositionWeights[j]* (int) FindClosestColor( Pixels[i][Row] ) ); 
   i++; j++;   
  }
  Buffer[k] = (ebmpBYTE) Index;
  k++;
 }
 return true;
}

bool BMP::Write1bitRow(  ebmpBYTE* Buffer, int BufferSize, int Row )
{ 
 int PositionWeights[8]  = {128,64,32,16,8,4,2,1};
 
 int i=0;
 int j;
 int k=0;
 if( Width > 8*BufferSize )
 { return false; }
 while( i < Width )
 {
  j=0;
  int Index = 0;
  while( j < 8 && i < Width )
  {
   Index += ( PositionWeights[j]* (int) FindClosestColor( Pixels[i][Row] ) ); 
   i++; j++;   
  }
  Buffer[k] = (ebmpBYTE) Index;
  k++;
 }
 return true;
}

ebmpBYTE BMP::FindClosestColor( RGBApixel& input )
{
 using namespace std;
 
 int i=0;
 int NumberOfColors = TellNumberOfColors();
 ebmpBYTE BestI = 0;
 int BestMatch = 999999;
  
 while( i < NumberOfColors )
 {
  RGBApixel Attempt = GetColor( i );
  int TempMatch = IntSquare( (int) Attempt.Red - (int) input.Red )
                + IntSquare( (int) Attempt.Green - (int) input.Green )
                + IntSquare( (int) Attempt.Blue - (int) input.Blue );
  if( TempMatch < BestMatch )
  { BestI = (ebmpBYTE) i; BestMatch = TempMatch; }
  if( BestMatch < 1 )
  { i = NumberOfColors; }
  i++;
 }
 return BestI;
}

bool EasyBMPcheckDataSize( void )
{
 using namespace std;
 bool ReturnValue = true;
 if( sizeof( ebmpBYTE ) != 1 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: ebmpBYTE has the wrong size (" 
        << sizeof( ebmpBYTE ) << " bytes)," << endl
	    << "               Compared to the expected 1 byte value" << endl;
  }
  ReturnValue = false;
 }
 if( sizeof( ebmpWORD ) != 2 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: ebmpWORD has the wrong size (" 
        << sizeof( ebmpWORD ) << " bytes)," << endl
	    << "               Compared to the expected 2 byte value" << endl;
  }
  ReturnValue = false;
 }
 if( sizeof( ebmpDWORD ) != 4 )
 {
  if( EasyBMPwarnings )
  {
   cout << "EasyBMP Error: ebmpDWORD has the wrong size (" 
        << sizeof( ebmpDWORD ) << " bytes)," << endl
	    << "               Compared to the expected 4 byte value" << endl;
  }
  ReturnValue = false;
 }
 return ReturnValue;
}

bool Rescale( BMP& InputImage , char mode, int NewDimension )
{
 using namespace std;
 int CapMode = toupper( mode );

 BMP OldImage( InputImage );
 
 if( CapMode != 'P' &&
     CapMode != 'W' &&
     CapMode != 'H' && 
     CapMode != 'F' )
 {
  if( EasyBMPwarnings )
  {
   char ErrorMessage [1024];
   sprintf( ErrorMessage, "EasyBMP Error: Unknown rescale mode %c requested\n" , mode );
   cout << ErrorMessage; 
  }
  return false;
 }

 int NewWidth  =0;
 int NewHeight =0;
 
 int OldWidth = OldImage.TellWidth();
 int OldHeight= OldImage.TellHeight();
 
 if( CapMode == 'P' )
 {
  NewWidth = (int) floor( OldWidth * NewDimension / 100.0 );
  NewHeight = (int) floor( OldHeight * NewDimension / 100.0 );
 }
 if( CapMode == 'F' )
 {
  if( OldWidth > OldHeight )
  { CapMode = 'W'; }
  else
  { CapMode = 'H'; }
 }

 if( CapMode == 'W' )
 {
  double percent = (double) NewDimension / (double) OldWidth;
  NewWidth = NewDimension;
  NewHeight = (int) floor( OldHeight * percent );
 }
 if( CapMode == 'H' )
 {
  double percent = (double) NewDimension / (double) OldHeight;
  NewHeight = NewDimension;
  NewWidth = (int) floor( OldWidth * percent );
 }
 
 if( NewWidth < 1 )
 { NewWidth = 1; }
 if( NewHeight < 1 )
 { NewHeight = 1; }
 
 InputImage.SetSize( NewWidth, NewHeight );
 InputImage.SetBitDepth( 24 );

 int I,J;
 double ThetaI,ThetaJ;
 
 for( int j=0; j < NewHeight-1 ; j++ )
 {
  ThetaJ = (double)(j*(OldHeight-1.0))
          /(double)(NewHeight-1.0);
  J	= (int) floor( ThetaJ );
  ThetaJ -= J;  
  
  for( int i=0; i < NewWidth-1 ; i++ )
  {
   ThetaI = (double)(i*(OldWidth-1.0))
           /(double)(NewWidth-1.0);
   I = (int) floor( ThetaI );
   ThetaI -= I;  
   
   InputImage(i,j)->Red = (ebmpBYTE) 
                          ( (1.0-ThetaI-ThetaJ+ThetaI*ThetaJ)*(OldImage(I,J)->Red)
                           +(ThetaI-ThetaI*ThetaJ)*(OldImage(I+1,J)->Red)   
                           +(ThetaJ-ThetaI*ThetaJ)*(OldImage(I,J+1)->Red)   
                           +(ThetaI*ThetaJ)*(OldImage(I+1,J+1)->Red) );
   InputImage(i,j)->Green = (ebmpBYTE) 
                          ( (1.0-ThetaI-ThetaJ+ThetaI*ThetaJ)*OldImage(I,J)->Green
                           +(ThetaI-ThetaI*ThetaJ)*OldImage(I+1,J)->Green   
                           +(ThetaJ-ThetaI*ThetaJ)*OldImage(I,J+1)->Green   
                           +(ThetaI*ThetaJ)*OldImage(I+1,J+1)->Green );  
   InputImage(i,j)->Blue = (ebmpBYTE) 
                          ( (1.0-ThetaI-ThetaJ+ThetaI*ThetaJ)*OldImage(I,J)->Blue
                           +(ThetaI-ThetaI*ThetaJ)*OldImage(I+1,J)->Blue   
                           +(ThetaJ-ThetaI*ThetaJ)*OldImage(I,J+1)->Blue   
                           +(ThetaI*ThetaJ)*OldImage(I+1,J+1)->Blue ); 
  }
   InputImage(NewWidth-1,j)->Red = (ebmpBYTE) 
                            ( (1.0-ThetaJ)*(OldImage(OldWidth-1,J)->Red)
                          + ThetaJ*(OldImage(OldWidth-1,J+1)->Red) ); 
   InputImage(NewWidth-1,j)->Green = (ebmpBYTE) 
                            ( (1.0-ThetaJ)*(OldImage(OldWidth-1,J)->Green)
                          + ThetaJ*(OldImage(OldWidth-1,J+1)->Green) ); 
   InputImage(NewWidth-1,j)->Blue = (ebmpBYTE) 
                            ( (1.0-ThetaJ)*(OldImage(OldWidth-1,J)->Blue)
                          + ThetaJ*(OldImage(OldWidth-1,J+1)->Blue) ); 
 } 

 for( int i=0 ; i < NewWidth-1 ; i++ )
 {
  ThetaI = (double)(i*(OldWidth-1.0))
          /(double)(NewWidth-1.0);
  I = (int) floor( ThetaI );
  ThetaI -= I;  
  InputImage(i,NewHeight-1)->Red = (ebmpBYTE) 
                            ( (1.0-ThetaI)*(OldImage(I,OldHeight-1)->Red)
                          + ThetaI*(OldImage(I,OldHeight-1)->Red) ); 
  InputImage(i,NewHeight-1)->Green = (ebmpBYTE) 
                            ( (1.0-ThetaI)*(OldImage(I,OldHeight-1)->Green)
                          + ThetaI*(OldImage(I,OldHeight-1)->Green) ); 
  InputImage(i,NewHeight-1)->Blue = (ebmpBYTE) 
                            ( (1.0-ThetaI)*(OldImage(I,OldHeight-1)->Blue)
                          + ThetaI*(OldImage(I,OldHeight-1)->Blue) ); 
 }
 
 *InputImage(NewWidth-1,NewHeight-1) = *OldImage(OldWidth-1,OldHeight-1);
 return true;
}

/*************************************************
*                                                *
*  EasyBMP Cross-Platform Windows Bitmap Library * 
*                                                *
*  Author: Paul Macklin                          *
*   email: pmacklin@math.uci.edu                 *
*                                                *
*    file: EasyBMP_Geometry.h                    *
*    date: 2-21-2005                             *
* version: 1.05.00                               *
*                                                *
*   License: BSD (revised)                       *
* Copyright: 2005-2006 by the EasyBMP Project    * 
*                                                *
* description: draw simple geometric objects     *
*                                                *
*************************************************/

#include "EasyBMP_Geometry.h"

int ebmpRound( double input )
{
 double output = floor( input );
 if( output - input >= 0.50 )
 { return (int) ( output+1 ); }
 return (int) output;
}

double InverseAngle( double Xdir, double Ydir )
{
 double pi = 3.14159265358979;
 double Norm = sqrt( Xdir*Xdir + Ydir*Ydir );
 if( Norm <= 0.25 )
 { return 0.0; }
 Xdir /= Norm; 
 Ydir /= Norm;

 double Xabs = fabs( Xdir );
 double Yabs = fabs( Ydir );
 double theta = 0.5*( acos( Xabs ) + asin( Yabs ) );

 if( Xdir >= 0.0 && Ydir >= 0.0 )
 { return theta; }
 if( Xdir < 0.0 && Ydir >= 0.0 )
 { return pi - theta; }
 if( Xdir < 0.0 && Ydir < 0.0 )
 { return pi + theta; }
 return 2*pi - theta; 
}

double LineFunction( double SlopeX , double SlopeY, int StartX, int StartY, double TestX, double TestY )
{
 return fabs( SlopeX*(TestY-StartY) - SlopeY*(TestX-StartX) );
}

void DrawAALine( BMP &Image , int FromX, int FromY, int ToX, int ToY , RGBApixel Color )
{
 double SlopeX = ToX-FromX;
 double SlopeY = ToY-FromY;

 if( fabs( SlopeX ) <= 0.8 && fabs( SlopeY ) <= 0.8 ) // nothing to do; don't bother
 {
  return;
 }
 double Norm = sqrt( Square( SlopeX ) + Square( SlopeY ) );
 SlopeX /= Norm; 
 SlopeY /= Norm;

 // bounds checking

 if( FromX >= Image.TellWidth() )
 { FromX = Image.TellWidth()-1; }
 if( FromX < 0 )
 { FromX = 0; }
 if( ToX >= Image.TellWidth() )
 { ToX = Image.TellWidth()-1; }
 if( ToX < 0 )
 { ToX = 0; }

 if( FromY >= Image.TellHeight() )
 { FromY = Image.TellHeight()-1; }
 if( FromY < 0 )
 { FromY = 0; }
 if( ToY >= Image.TellHeight() )
 { ToY = Image.TellHeight()-1; }
 if( ToY < 0 )
 { ToY = 0; }

 int LeftI = FromX;
 int RightI = ToX;
 if( RightI < LeftI ){ int temp = LeftI; LeftI = RightI; RightI = temp; }
 int LeftJ = FromY;
 int RightJ = ToY;
 if( RightJ < LeftJ ){ int temp = LeftJ; LeftJ = RightJ; RightJ = temp; }
 
 int i,j;
 for( i=LeftI ; i <= RightI ; i++ )
 {
  for( j=LeftJ ; j <= RightJ ; j++ )
  {
   double ii=0;
   double jj=0;
   double dx = 0.25;
   double dy = 0.25;
   double x = i-1.5*dx;
   double y = j-1.5*dx;
   
   double Temp = 0.0;
   
   for( ii=-2; ii<=1 ; ii++)
   {
    for( jj=-2 ; jj<=1 ; jj++)
    {
     x = i+ii*dx+0.5*dx;
     y = j+jj*dy+0.5*dy;
     double Temp1 = LineFunction( SlopeX, SlopeY , FromX, FromY, x,y ); 
     if( Temp1 <= 0.5 ){ Temp1 = 1.0; }else{ Temp1 = 0.0; }
     Temp+=Temp1;
    }   
   }
   
   Temp /= 16.0;
   double MinValue = 0.03125; // 1.0/32.0
   
   if( Temp > MinValue )
   {
    Image(i,j)->Red = (ebmpBYTE) (unsigned int) (  (1.0-Temp)*( (double) Image(i,j)->Red )
                                                        +Temp*( (double) Color.Red ) );
    Image(i,j)->Green = (ebmpBYTE) (unsigned int) (  (1.0-Temp)*( (double) Image(i,j)->Green )
                                                        +Temp*( (double) Color.Green ) );
    Image(i,j)->Blue = (ebmpBYTE) (unsigned int) (  (1.0-Temp)*( (double) Image(i,j)->Blue )
                                                          +Temp*( (double) Color.Blue ) );
   }
   
  }
 }
 
 return; 
}

void DrawFastLine( BMP &Image , int FromX, int FromY, int ToX, int ToY , RGBApixel Color )
{
 // bounds checking

 if( FromX >= Image.TellWidth() )
 { FromX = Image.TellWidth()-1; }
 if( FromX < 0 )
 { FromX = 0; }
 if( ToX >= Image.TellWidth() )
 { ToX = Image.TellWidth()-1; }
 if( ToX < 0 )
 { ToX = 0; }

 if( FromY >= Image.TellHeight() )
 { FromY = Image.TellHeight()-1; }
 if( FromY < 0 )
 { FromY = 0; }
 if( ToY >= Image.TellHeight() )
 { ToY = Image.TellHeight()-1; }
 if( ToY < 0 )
 { ToY = 0; }

 // source: http://www.gamedev.net/reference/articles/article1275.asp

 int dX = ToX - FromX;
 int dY = ToY - FromY;
 
 if( dX == 0 && dY == 0 ) // nothing to do; don't bother
 {
  return;
 }
 
 int Xinc1 = 1;
 if( dX < 0 )
 { Xinc1 = -1; dX = -dX; } 
 int Yinc1 = 1;
 if( dY < 0 )
 { Yinc1 = -1; dY = -dY; }
 
 int x = FromX;               // Start x off at the first pixel
 int y = FromY;               // Start y off at the first pixel
 
 int Xinc2 = Xinc1;
 int Yinc2 = Yinc1;
 
 double Denominator;
 double Numerator;
 int NumberToAdd;
 int NumberOfPixels;

 if ( dX >= dY )         // There is at least one x-value for every y-value
 {
  Xinc1 = 0;                  // Don't change the x when numerator >= denominator
  Yinc2 = 0;                  // Don't change the y for every iteration
  Denominator = dX+0.0;
  Numerator = 0.5*dX;
  NumberToAdd = dY;
  NumberOfPixels = dX;         // There are more x-values than y-values
 }
 else                          // There is at least one y-value for every x-value
 {
  Xinc2 = 0;                  // Don't change the x for every iteration
  Yinc1 = 0;                  // Don't change the y when numerator >= denominator
  Denominator = dY+0.0;
  Numerator = 0.5*dY;
  NumberToAdd = dX;
  NumberOfPixels = dY;         // There are more y-values than x-values
 }
 
 int CurrentPixel;

 for (CurrentPixel = 0; CurrentPixel <= NumberOfPixels; CurrentPixel++ )
 {
  Image(x,y)->Red = Color.Red;
  Image(x,y)->Green = Color.Green;
  Image(x,y)->Blue = Color.Blue;
  
  Numerator += NumberToAdd;   // Increase the numerator by the top of the fraction
  if( Numerator >= Denominator ) // Check if numerator >= denominator
  {
    Numerator -= Denominator; // Calculate the new numerator value
    x += Xinc1;               // Change the x as appropriate
    y += Yinc1;               // Change the y as appropriate
  }
  x += Xinc2;                 // Change the x as appropriate
  y += Yinc2;                 // Change the y as appropriate
 }
 
 return; 
}

void DrawArc( BMP &Image , double CenterX, double CenterY , double Radius, 
              double FromTheta, double ToTheta , RGBApixel Color )
{
 double pi = 3.14159265358979;

 while( ToTheta < FromTheta )
 { ToTheta += 2*pi; }

 double Arclength = (ToTheta-FromTheta)*Radius;
 if( fabs( Arclength ) <= 1e-5 ) // if it's short, don't bother
 { return; }
 
 // set up the final circle first
 
 BMP Downsampled;
 int FinalWidth = (int) floor( 2.0*Radius + 1.0); // was ceil ,also tried Round
 
 // new for testing
 Radius = 0.5*(FinalWidth-1.0);
 // end new for testing 
 
 int FinalHeight = FinalWidth;
 Downsampled.SetSize( FinalWidth , FinalHeight );
 
 // make a temporary circle of double resolution

 BMP Temp;
 double TempRadius = 2.0*Radius; 
 
 Temp.SetSize( 2*FinalWidth, 2*FinalHeight );
 //double dTheta = 1.0/TempRadius;
 
 double CenterXtemp = FinalWidth - 0.5; // was TempRadius + .5
 double CenterYtemp = FinalHeight - 0.5; // was TempRadius + 0.5;

 int x,y;
 
 double OuterRadiusSquared = TempRadius+1.0;
 OuterRadiusSquared *= OuterRadiusSquared;
 double InnerRadiusSquared = TempRadius-1.0;
 InnerRadiusSquared *= InnerRadiusSquared;
 
 for( x=0 ; x < Temp.TellWidth() ;x++)
 {
  for( y=0 ; y < Temp.TellHeight() ; y++)
  {
   double X = x-CenterXtemp;
   double Y = y-CenterYtemp;
   double TempRadiusSquared = X*X + Y*Y;
   
   if( InnerRadiusSquared <= TempRadiusSquared && 
       TempRadiusSquared <= OuterRadiusSquared )
   {
    double Angle = InverseAngle( X, Y );
    bool PlotIt = false;
    if( FromTheta <= Angle && Angle <= ToTheta )
    { PlotIt = true; }
    Angle += 2*pi;
    if( FromTheta <= Angle && Angle <= ToTheta )
    { PlotIt = true; }
    Angle -= 4*pi;
    if( FromTheta <= Angle && Angle <= ToTheta )
    { PlotIt = true; }
    
    if( PlotIt )
    { Temp(x,y)->Red = 0; }
   }
  }
 }
 
 // downsample to anti-alias
 
 int i,j;
 for( i=0 ; i < Downsampled.TellWidth() ; i++ )
 {
  for( j=0 ; j < Downsampled.TellHeight() ; j++ )
  {
   double TempRed = 0.0;
  
   int k,ell;
   for( k=0 ; k <= 1 ; k++ )
   {
    for( ell=0 ; ell <= 1 ; ell++ )
    {
     int I = 2*i+k;
     int J = 2*j+ell;
     TempRed += (double) Temp(I,J)->Red;
    }
   }
   TempRed /= 4.0;
   
   Downsampled(i,j)->Red = (ebmpBYTE) TempRed;
  }
 }
 
 // paste with alpha blending 
 
 int DestinationTopLeft = ebmpRound( CenterX - Radius );
 int DestinationTopRight = ebmpRound( CenterY - Radius );
 
 for( i=0 ; i < Downsampled.TellWidth() ; i++) 
 {
  for( j=0 ; j < Downsampled.TellHeight() ; j++)
  {
   int DestinationI = DestinationTopLeft+i;
   int DestinationJ = DestinationTopRight+j;
   if( DestinationI >= 0 && DestinationI < Image.TellWidth() &&
       DestinationJ >= 0 && DestinationJ < Image.TellHeight() )
   {
    double alpha = (255.0 - Downsampled(i,j)->Red )/255.0;
    Image(DestinationI,DestinationJ)->Red = (ebmpBYTE) ( 
      (1.0-alpha)*Image(DestinationI,DestinationJ)->Red 
    + (alpha)*Color.Red );
    Image(DestinationI,DestinationJ)->Green = (ebmpBYTE) ( 
      (1.0-alpha)*Image(DestinationI,DestinationJ)->Green 
    + (alpha)*Color.Green );
    Image(DestinationI,DestinationJ)->Blue = (ebmpBYTE) ( 
      (1.0-alpha)*Image(DestinationI,DestinationJ)->Blue 
    + (alpha)*Color.Blue );
   }
  
  }
 }
 
 return;
}

void DrawLine( BMP &Image , int FromX , int FromY, int ToX, int ToY, RGBApixel Color )
{
 if( FromX != ToX && FromY != ToY )
 {
  DrawAALine( Image, FromX, FromY, ToX, ToY, Color);
 } 
 DrawFastLine( Image, FromX, FromY, ToX, ToY, Color); 
 return;
}


/*************************************************
*                                                *
*  EasyBMP Cross-Platform Windows Bitmap Library * 
*                                                *
*  Author: Paul Macklin                          *
*   email: pmacklin@math.uci.edu                 *
*                                                *
*    file: EasyBMP_Font.h                        *
*    date: 2-21-2005                             *
* version: 1.05.00                               *
*                                                *
*   License: BSD (revised)                       *
* Copyright: 2005-2006 by the EasyBMP Project    * 
*                                                *
* description: draw a simple font                *
*                                                *
*************************************************/

#include "EasyBMP_Geometry.h"
#include "EasyBMP_Font.h"
				  
int PrintString( BMP& Image, char* String , int TopLeftX, int TopLeftY , int Height , 
                  RGBApixel Color )
{
 int CharNumber = 0;
 int StartX = TopLeftX;
 int Spacing = (int) ebmpRound( 0.2*Height );
 if( Spacing < 3 )
 { Spacing = 3; }
 
 for( CharNumber = 0 ; CharNumber < int(strlen( String )) ; CharNumber++ )
 {
  int ReturnPosition = PrintLetter( Image , String[CharNumber] , StartX , TopLeftY , Height , Color );
  StartX = ReturnPosition;
  StartX += Spacing;
 }
 return StartX;
}

int PrintLetter( BMP& Image, char Letter , int TopLeftX, int TopLeftY, int Height , 
                  RGBApixel Color )
{
 int Width = (int) floor( 0.6*Height);
 if( Width % 2 != 0 ){ Width++; }
 int Center = (Width)/2;
 
 //RGBApixel TempColor;
 //TempColor.Red = 0;
 //TempColor.Green = 255;
 //TempColor.Blue = 0;
 
 double pi = 3.14159265358979;

// if( isalpha(Letter) )
// { Letter = toupper(Letter); }

 if( Letter == COPYRIGHT_SYMBOL )
 {
  return PrintCopyright( Image, TopLeftX, TopLeftY, Height, Color );
 }

 if( Letter == 'a'  )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x2 = ebmpRound(TopLeftX+0.5*Height);
  int y2 = ebmpRound(TopLeftY+0.5*Height);
  
  int x3 = x2;
  int y3 = TopLeftY+Height;
  
  DrawArc(Image,x1,y1,0.25*Height,0,2*pi,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
 
  return ebmpRound( TopLeftX + 0.5*Height );
 }
 
 if( Letter == 'b' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x2 = TopLeftX; // ebmpRound(TopLeftX+0.5*Height);
  int y2 = TopLeftY; // ebmpRound(TopLeftY+0.5*Height);
  
  int x3 = x2;
  int y3 = TopLeftY+Height;
  
  DrawArc(Image,x1,y1,0.25*Height,0,2*pi,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
 
  return ebmpRound( TopLeftX + 0.5*Height );
 } 
 
 if( Letter == 'c' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;

  DrawArc(Image,x1,y1,0.25*Height,0.25*pi,-0.25*pi,Color);
  return ebmpRound( TopLeftX+0.5*Height);
 }

 if( Letter == 'd' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x2 = ebmpRound(TopLeftX+0.5*Height);
  int y2 = TopLeftY; // ebmpRound(TopLeftY+0.5*Height);
  
  int x3 = x2;
  int y3 = TopLeftY+Height;
  
  DrawArc(Image,x1,y1,0.25*Height,0,2*pi,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
 
  return ebmpRound( TopLeftX + 0.5*Height );
 }  
 
 if( Letter == 'e' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x2 = TopLeftX;
  int y2 = ebmpRound(TopLeftY + 0.75*Height);
  
  int x3 = ebmpRound( TopLeftX+0.5*Height);
  int y3 = y2;

  DrawArc(Image,x1,y1,0.25*Height,0.25*pi,0,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
  
  return x3;
 } 
 
 if( Letter == 'f' )
 {
  int x1 = ebmpRound( TopLeftX + 0.25*Height);
  int y1 = TopLeftY + Center;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = TopLeftX;
  int y3 = ebmpRound( TopLeftY + 0.5*Height);
  
  int x4 = x1 + (x1-x3);
  int y4 = y3;
  
  double x5 = TopLeftX+0.5*Height;
  double y5 = TopLeftY+0.25*Height;
  
  if( Height % 4 == 3 )
  { x5 -= 1; }
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x3,y3,x4,y4,Color);
  
  DrawArc(Image,x5,y5,0.25*Height,7*pi/8    ,2*pi,Color);

  return x4;  
 }
 
 if( Letter == 'g' )
 {
  double x1 = TopLeftX+0.25*Height;
  double y1 = TopLeftY+0.75*Height;
 
  int x2 = ebmpRound(TopLeftX+0.5*Height);
  int y2 = ebmpRound(TopLeftY+0.5*Height);
  
  int x3 = x2;
  int y3 = ebmpRound(TopLeftY+1.25*Height);
  
  double x4 = x1; 
  double y4 = TopLeftY+1.25*Height;
 
  DrawArc(Image,x1,y1,0.25*Height,0,2*pi,Color);
  DrawArc(Image,x4,y4,0.25*Height,0,pi,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
 
  return ebmpRound(TopLeftX+0.5*Height);
 }
 
 if( Letter == 'h' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x3 = TopLeftX;
  int y3 = TopLeftY; // ebmpRound(TopLeftY+0.5*Height);
  
  int x4 = x3;
  int y4 = TopLeftY + Height;
  
  int x5 = ebmpRound(TopLeftX+0.5*Height);
  int y5 = ebmpRound(TopLeftY+0.75*Height);
  
  int x6 = x5;
  int y6 = y4;
  
  DrawArc(Image,x1,y1,0.25*Height,pi,2*pi,Color);
  
  DrawLine(Image,x3,y3,x4,y4,Color);
  DrawLine(Image,x5,y5,x6,y6,Color);
 
  return x5;
 }  
 
 if( Letter == 'i' )
 {
  int x1 = TopLeftX;
  int y1 = ebmpRound(TopLeftY+0.5*Height);
   
  int x2 = x1;
  int y2 = TopLeftY+Height;
  
  double x3 = x1;
  double y3 = y1 - 2.5;
 
  DrawArc( Image, x3, y3, 0.75 , 0 , 6.3 , Color );
  DrawLine(Image,x1,y1,x2,y2,Color);
  
  return ebmpRound(x1+1.25);
 }
 
 if( Letter == 'j' )
 {
  int x1 = ebmpRound(TopLeftX+0.25*Height);
  int y1 = ebmpRound(TopLeftY+0.5*Height);
   
  int x2 = x1;
  int y2 = ebmpRound(TopLeftY+1.25*Height);
  
  double x3 = x1;
  double y3 = y1 - 2.5;
  
  double x4 = TopLeftX;
  double y4 = TopLeftY+1.25*Height;
 
  DrawArc( Image, x3, y3, 0.75 , 0 , 6.3 , Color );
  DrawLine(Image,x1,y1,x2,y2,Color);
  
  DrawArc(Image,x4,y4,0.25*Height,0,pi,Color);
  
  return x1;
 } 
 
 if( Letter == 'k' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY+Height;
  
  int x3 = x1;
  int y3 = ebmpRound(TopLeftY+0.75*Height);
  
  int x4 = ebmpRound(TopLeftX+0.3*Height);
  int y4 = ebmpRound(TopLeftY+0.5*Height);
  
  int x5 = x4;
  int y5 = y2;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x3,y3,x4,y4,Color);
  DrawLine(Image,x3,y3,x5,y5,Color);
 
  return x5;
 }
 
 if( Letter == 'm' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;

  double x2 = TopLeftX + 0.75*Height;
  double y2 = y1;  
  
  int x3 = TopLeftX;
  int y3 = ebmpRound(TopLeftY+0.5*Height);
  
  int x4 = x3;
  int y4 = TopLeftY + Height;
  
  int x5 = ebmpRound(TopLeftX+0.5*Height);
  int y5 = ebmpRound(TopLeftY+0.75*Height);
  
  int x6 = x5;
  int y6 = y4;
  
  int x7 = ebmpRound(TopLeftX+Height);
  if( x7 - x5 > x5 - x3 )
  { x7--; }
  
  int y7 = y5;
  
  int x8 = x7;
  int y8 = y4;
  
  
  DrawArc(Image,x1,y1,0.25*Height,pi,2*pi,Color);
  DrawArc(Image,x2,y2,0.25*Height,pi,2*pi,Color);
  
  DrawLine(Image,x3,y3,x4,y4,Color);
  DrawLine(Image,x5,y5,x6,y6,Color);
  DrawLine(Image,x7,y7,x8,y8,Color);
 
  return x7;
 }
 
 if( Letter == 'n' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x3 = TopLeftX;
  int y3 = ebmpRound(TopLeftY+0.5*Height);
  
  int x4 = x3;
  int y4 = TopLeftY + Height;
  
  int x5 = ebmpRound(TopLeftX+0.5*Height);
  int y5 = ebmpRound(TopLeftY+0.75*Height);
  
  int x6 = x5;
  int y6 = y4;
  
  DrawArc(Image,x1,y1,0.25*Height,pi,2*pi,Color);
  
  DrawLine(Image,x3,y3,x4,y4,Color);
  DrawLine(Image,x5,y5,x6,y6,Color);
 
  return x5;
 } 
 
 if( Letter == 'o' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  DrawArc(Image,x1,y1,0.25*Height,0,2*pi,Color);
 
  return ebmpRound(TopLeftX + 0.5*Height);
 }   
 
 if( Letter == 'p' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x2 = TopLeftX;
  int y2 = ebmpRound(TopLeftY + 0.5*Height);
  
  int x3 = x2;
  int y3 = ebmpRound(TopLeftY + 1.5*Height);

  DrawArc(Image,x1,y1,0.25*Height,0,2*pi,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);

  return ebmpRound( TopLeftX + 0.5*Height );
 }
 
 if( Letter == 'q' )
 {
  double x1 = TopLeftX+0.25*Height;
  double y1 = TopLeftY+0.75*Height;
 
  int x2 = ebmpRound(TopLeftX+0.5*Height);
  int y2 = ebmpRound(TopLeftY+0.5*Height);
  
  int x3 = x2;
  int y3 = ebmpRound(TopLeftY+1.5*Height);

  int x4 = ebmpRound(x3+0.2*Height);
  int y4 = ebmpRound(y3-0.2*Height);
 
  DrawArc(Image,x1,y1,0.25*Height,0,2*pi,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
  DrawLine(Image,x3,y3,x4,y4,Color);
 
  return ebmpRound(TopLeftX+0.5*Height);
 }
 
 if( Letter == 'r' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x3 = TopLeftX;
  int y3 = ebmpRound(TopLeftY+0.5*Height);
  
  int x4 = x3;
  int y4 = TopLeftY + Height;

/*  
  int x5 = ebmpRound(TopLeftX+0.5*Height);
  int y5 = ebmpRound(TopLeftY+0.75*Height);
  
  int x6 = x5;
  int y6 = y4;
*/  
  
  DrawArc(Image,x1,y1,0.25*Height,pi,2*pi,Color);
  
  DrawLine(Image,x3,y3,x4,y4,Color);
//  DrawLine(Image,x5,y5,x6,y6,Color);
 
  return ebmpRound(TopLeftX+0.5*Height);
 }  
 
 if( Letter == 's' )
 {
  double x1 = TopLeftX+0.125*Height;
  double y1 = TopLeftY+0.625*Height;

  double x2 = x1;
  double y2 = (TopLeftY+0.875*Height);
  
  double difference = (TopLeftY+Height)-y2;
  double MaxAngle1 = 0;
  //double MaxAngle2 = pi; REvisar por las dudas
  //if( difference < 1.5 )
  //{ difference = 1.5; MaxAngle1 = 0; MaxAngle2 = 1.5; x1 = TopLeftX + difference; x2 = x1; }
  
  y1 = y2 - 2*difference;
  
  DrawArc(Image,x1,y1,difference,0.5*pi,MaxAngle1,Color);
  DrawArc(Image,x2,y2,difference,-0.5*pi,pi,Color);
 
  return ebmpRound(TopLeftX+2*difference);
 }
 
 if( Letter == 't' )
 {
  int x1 = ebmpRound( TopLeftX + 0.25*Height);
  int y1 = TopLeftY + Center;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = TopLeftX;
  int y3 = ebmpRound( TopLeftY + 0.5*Height);
  
  int x4 = x1 + (x1-x3);
  int y4 = y3;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x3,y3,x4,y4,Color);

  return x4; 
 }
 
 if( Letter == 'u' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.75*Height;
  
  int x3 = TopLeftX;
  int y3 = ebmpRound(TopLeftY+0.5*Height);
  
  int x4 = x3;
  int y4 = ebmpRound(TopLeftY+0.75*Height);//  + Height;
  
  int x5 = ebmpRound(TopLeftX+0.5*Height);
  int y5 = TopLeftY + Height;// ebmpRound(TopLeftY+0.75*Height);
  
  int x6 = x5;
  int y6 = y3;
  
  DrawArc(Image,x1,y1,0.25*Height,0,pi,Color);
  
  DrawLine(Image,x3,y3,x4,y4,Color);
  DrawLine(Image,x5,y5,x6,y6,Color);
 
  return x5;
 }  
 
 if( Letter == 'v' )
 {
  int x1 = TopLeftX;
  int y1 = ebmpRound(TopLeftY+0.5*Height);
  
  int x2 = ebmpRound( TopLeftX+0.2*Height);
  int y2 = TopLeftY+Height;
  
  int x3 = ebmpRound( TopLeftX+0.4*Height);
  int y3 = y1;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
 
  return x3;
 }

 if( Letter == 'w' )
 {
  int x1 = TopLeftX;
  int y1 = ebmpRound(TopLeftY+0.5*Height);
  
  int x2 = ebmpRound(TopLeftX+0.2*Height);
  int y2 = TopLeftY+Height;
  
  int x3 = ebmpRound(TopLeftX+0.4*Height);
  int y3 = y1;
  
  int x4 = ebmpRound(x3+0.2*Height);
  int y4 = y2;
  
  int x5 = ebmpRound(x3+0.4*Height);
  int y5 = y1;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
  DrawLine(Image,x3,y3,x4,y4,Color);
  DrawLine(Image,x4,y4,x5,y5,Color);
  
  return x5;
 }
 
 if( Letter == 'x' )
 {
  int x1 = TopLeftX;
  int y1 = ebmpRound(TopLeftY+0.5*Height);
  
  int x2 = ebmpRound(TopLeftX+0.5*Height);
  int y2 = y1;
  
  int x3 = x1;
  int y3 = TopLeftY+Height;
  
  int x4 = x2;
  int y4 = y3;
  
  DrawLine(Image,x1,y1,x4,y4,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
 
  return x4;
 }
 
 if( Letter == 'y' )
 {
  int x1 = TopLeftX;
  int y1 = ebmpRound(TopLeftY+0.5*Height);
  
  int x2 = ebmpRound(TopLeftX+0.5*Height);
  int y2 = y1;
  
  int x3 = ebmpRound(x1+0.25*Height);
  int y3 = TopLeftY+Height;
  
  int x4 = x1;
  int y4 = ebmpRound(TopLeftY+1.25*Height)+1;
  
  DrawLine(Image,x1,y1,x3,y3,Color);
  DrawLine(Image,x2,y2,x4,y4,Color);
 
  return x2;
 } 
 
 if( Letter == 'z' )
 {
  int x1 = TopLeftX;
  int y1 = ebmpRound(TopLeftY+0.5*Height);
  
  int x2 = ebmpRound(TopLeftX+0.5*Height);
  int y2 = y1;
  
  int x3 = x1;
  int y3 = TopLeftY+Height;
  
  int x4 = x2;
  int y4 = y3;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
  DrawLine(Image,x3,y3,x4,y4,Color);
  
  return x4;
 }
 
 if( Letter == 'A' )
 {
  // define some control points
  
  int x1 = TopLeftX;
  int y1 = TopLeftY+Height;
  
  int x2 = TopLeftX + ebmpRound( 0.3*Height );
  int y2 = TopLeftY;
  
  int x3 = TopLeftX + ebmpRound( 0.6*Height );
  int y3 = y1;
  
  int x4 = TopLeftX + ebmpRound( 0.1*Height );
  int y4 = ebmpRound( y1 - Height/3.0 );
  
  int x5 = ebmpRound( x3 - 0.1*Height ); 
  int y5 = y4;
 
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
  DrawLine( Image , x4, y4, x5, y5, Color );
 
  return x3; 
 }
 
 if( Letter == 'B' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY+Height;
  
  int x2 = TopLeftX;
  int y2 = TopLeftY;
  
  int x3 = TopLeftX + Center; // (int) ebmpRound( 0.3*Height );
  int y3 = TopLeftY;
  
  int x4 = x1;
  int y4 = (int) ebmpRound( TopLeftY + 0.5*Height );

  int x5 = x3;
  int y5 = y4;
  
  int x6 = x3;
  int y6 = y1;

  // centers of the circles
  
  double x7 = x3;
  double y7 = ( TopLeftY + 0.25*Height );

  double x8 = x3;
  double y8 = ( TopLeftY + 0.75*Height );
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
  
  DrawLine( Image , x2, y2, x3, y3, Color );  
  DrawLine( Image , x4, y4, x5, y5, Color );  
  DrawLine( Image , x1, y1, x6, y6, Color );
  
  DrawArc( Image, x7, y7 , 0.25*Height , -1.57079632679490 , 1.57079632679490 , Color ); 
  DrawArc( Image, x8, y8 , 0.25*Height , -1.57079632679490 , 1.57079632679490 , Color ); 
  
  return ebmpRound( TopLeftX + Center + 0.25*Height); 
 }
 
 if( Letter == 'C' )
 {
  double x5 = TopLeftX + Center; 
  double y5 = TopLeftY + Center; 

  double x6 = x5;
  double y6 = TopLeftY + Height - Center; 
  
  int x7 = TopLeftX;
  int y7 = (int) y5; 
  
  int x8 = x7;
  int y8 = (int) y6; 

  DrawArc( Image, x5, y5 , Center , -3.14159265358979 , 0 , Color ); 
  DrawArc( Image, x6, y6 , Center , 0 , 3.14159265358979, Color ); 
  
  DrawLine( Image , x7, y7, x8, y8, Color );
 
  return TopLeftX + Width; //  ebmpRound(TopLeftX+0.6*Height);
 } 
 
 if( Letter == 'D' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = TopLeftX + Center; // ebmpRound( TopLeftX + 0.3*Height );
  int y2 = y1;
  
  int x3 = TopLeftX;
  int y3 = TopLeftY+Height;
  
  int x4 = x2;
  int y4 = y3;
  
  double x5 = x2;
  double y5 = TopLeftY + Center; // TopLeftY + 0.3*Height;

  double x6 = x2;
  double y6 = TopLeftY + Height - Center; // TopLeftY + 0.7*Height;
  
  int x7 = TopLeftX + Width; // ebmpRound(TopLeftX + 0.6*Height);
  int y7 = (int) y5; // ebmpRound( y5 );
  
  int x8 = x7;
  int y8 = (int) y6; //  ebmpRound( y6 );
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x1, y1, x3, y3, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );

  DrawArc( Image, x5, y5 , Center , -1.57079632679490 , 0 , Color ); 
  DrawArc( Image, x6, y6 , Center , 0 , 1.57079632679490 , Color ); 

  DrawLine( Image , x7, y7, x8, y8, Color );
 
  return x7;
 }
 
 if( Letter == 'E' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = TopLeftX + Width;
  int y3 = TopLeftY;
  
  int x4 = TopLeftX;
  int y4 = ebmpRound( TopLeftY + 0.5*Height);
  
  int x5 = ebmpRound( TopLeftX + 0.45*Height);
  int y5 = y4;
  
  int x6 = TopLeftX + Width;
  int y6 = y2;

  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x1, y1, x3, y3, Color );
  DrawLine( Image , x4, y4, x5, y5, Color );
  DrawLine( Image , x2, y2, x6, y6, Color );
  
  return x6;
 }
 
 if( Letter == 'F' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = TopLeftX + Width;
  int y3 = TopLeftY;
  
  int x4 = TopLeftX;
  int y4 = ebmpRound( TopLeftY + 0.5*Height);
  
  int x5 = ebmpRound( TopLeftX + 0.45*Height); // x3;
  int y5 = y4;

  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x1, y1, x3, y3, Color );
  DrawLine( Image , x4, y4, x5, y5, Color );
  
  return x3;
 } 
 
 if( Letter == 'G' )
 {
  double x5 = TopLeftX + Center; 
  double y5 = TopLeftY + Center; 

  double x6 = x5;
  double y6 = TopLeftY + Height - Center; 
  
  int x7 = TopLeftX;
  int y7 = (int) y5; 
  
  int x8 = x7;
  int y8 = (int) y6; 
  
  int x9 = TopLeftX + Center; // ebmpRound( TopLeftX + 0.45*Height );
  int y9 = ebmpRound( TopLeftY + 0.6*Height );
  
  int x10 = TopLeftX + Width; // ebmpRound( TopLeftX + 0.65*Height );
  int y10 = y9;
  
  int x11 = x10;
  int y11 = TopLeftY + Height;

  DrawArc( Image, x5, y5 , Center , -3.14159265358979 , 0 , Color ); 
  DrawArc( Image, x6, y6 , Center , 0 , 3.14159265358979, Color ); 
  
  DrawLine( Image , x7, y7, x8, y8, Color );
  
  DrawLine( Image , x9, y9, x10 ,y10 ,Color );
  DrawLine( Image , x10, y10, x11 ,y11 ,Color );
 
  return x10; //  ebmpRound(TopLeftX+0.6*Height);
 }  
 
 if( Letter == 'H' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = TopLeftX + Width;
  int y3 = y1;
  
  int x4 = x3;
  int y4 = y2;
  
  int x5 = x1;
  int y5 = ebmpRound( TopLeftY + 0.5*Height );
  
  int x6 = x3;
  int y6 = y5;
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  DrawLine( Image , x5, y5, x6, y6, Color );

  return x3;
 }
 
 if( Letter == 'I' )
 {
  int x1 = ebmpRound( TopLeftX + Height*0.05);
  int y1 = TopLeftY;
  
  int x2 = ebmpRound(x1 + 0.4*Height);
  int y2 = y1;
  
  int x3 = ebmpRound( x1 + 0.2*Height);
  int y3 = y1;
  
  int x4 = x1;
  int y4 = TopLeftY+Height;
  
  int x5 = x2;
  int y5 = y4;
  
  int x6 = x3;
  int y6 = y4;
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x6, y6, Color );
  DrawLine( Image , x4, y4, x5, y5, Color );
  
  return x2;
 }
 
 if( Letter == 'J' )
 {
  int x1 = TopLeftX + Width;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY + Height - Center;
  
  double x3 = TopLeftX + Center;
  double y3 = y2;
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawArc( Image, x3, y3, Center , 0 , 1.1*pi , Color );
  return x1;
 }
 
 if( Letter == 'K' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = x1;
  int y3 = TopLeftY + Height - Center; // ebmpRound( TopLeftY + 0.6*Height );
  
  int x4 = TopLeftX + Width;
  int y4 = y1;
  
  int x5 = TopLeftX + Center;
  int y5 = ebmpRound( TopLeftY + 0.5*Height );
  
  int x6 = x4;
  int y6 = y2;
  
  DrawLine( Image, x1, y1, x2, y2, Color );
  DrawLine( Image, x3, y3, x4, y4, Color );
  DrawLine( Image, x5, y5, x6, y6, Color );
 
  return x4;
 }
 
 if( Letter == 'L' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = TopLeftX + Width;
  int y3 = y2;
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );

  return x3;
 }
  
 if( Letter == 'M' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = TopLeftX + Width;
  int y3 = y1;
  
  int x4 = x3;
  int y4 = y2;
  
  int x5 = TopLeftX + Center;
  int y5 = y4;

  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  DrawLine( Image , x1, y1, x5, y5, Color );
  DrawLine( Image , x3, y3, x5, y5, Color );
 
  return x3;
 } 
 
 if( Letter == 'N' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = TopLeftY + Height;
  
  int x3 = TopLeftX + Width;
  int y3 = y1;
  
  int x4 = x3;
  int y4 = y2;

  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  DrawLine( Image , x1, y1, x4, y4, Color );
 
  return x3;
 }

 if( Letter == 'P' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY+Height;
  
  int x2 = TopLeftX;
  int y2 = TopLeftY;
  
  int x3 = TopLeftX + Center; 
  int y3 = TopLeftY;
  
  int x4 = x1;
  int y4 = ebmpRound( TopLeftY + 0.5*Height );

  int x5 = x3;
  int y5 = y4;
  
  //int x6 = x3;
  //int y6 = y1;

  // centers of the circles
  
  double x7 = x3;
  double y7 = ( 0.5*(y3+y5) );

  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
  
  DrawLine( Image , x2, y2, x3, y3, Color );  
  DrawLine( Image , x4, y4, x5, y5, Color );  
  
  DrawArc( Image, x7, y7 , 0.25*Height , -1.57079632679490 , 1.57079632679490 , Color ); 
  
  return ebmpRound( TopLeftX + Center + 0.25*Height); 
 }
 
 if( Letter == 'Q' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY + Height - Center;
  
  int x2 = x1;
  int y2 = TopLeftY + Center; 
  
  int x3 = TopLeftX + Width;
  int y3 = y2;
  
  int x4 = x3;
  int y4 = y1;

  // centers of the circles
  
  double x5 = TopLeftX + Center; 
  double y5 = TopLeftY + Center; 

  double x6 = x5;
  double y6 = TopLeftY + Height - Center; 
  
  // more points
  
  int x7 = TopLeftX + Width;
  int y7 = TopLeftY + Height;
  
  int x8 = x7 - Center;
  int y8 = y7 - Center;
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  
  DrawArc( Image, x5, y5 , Center , 3.14159265358979 , 6.28318530717959 , Color ); 
  DrawArc( Image, x6, y6 , Center , 0 ,  3.14159265358979 , Color ); 
  
  DrawLine( Image , x7, y7 , x8, y8 , Color );
  
  return x3; 
 } 
 
 if( Letter == 'R' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY+Height;
  
  int x2 = TopLeftX;
  int y2 = TopLeftY;
  
  int x3 = TopLeftX + Center; 
  int y3 = TopLeftY;
  
  int x4 = x1;
  int y4 = ebmpRound( TopLeftY + 0.5*Height );

  int x5 = x3;
  int y5 = y4;
  
  //int x6 = x3;
  //int y6 = y1;
  
  // centers of the circles
  
  double x7 = x3;
  double y7 = ( 0.5*(y3+y5) );
  
  // more
  
  int x8 = TopLeftX + Width;
  int y8 = y1;
  
  int x9 = ebmpRound( TopLeftX + 0.25*Height);
  int y9 = y4;  

  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
  
  DrawLine( Image , x2, y2, x3, y3, Color );  
  DrawLine( Image , x4, y4, x5, y5, Color );  
  
  DrawArc( Image, x7, y7 , 0.25*Height , -1.57079632679490 , 1.57079632679490 , Color ); 
  
  DrawLine( Image , x8, y8, x9, y9 , Color);
  
  return TopLeftX + Width; 
 } 
 
 if( Letter == 'T' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
    
  int x2 = TopLeftX + Width;
  int y2 = y1; 
  
  int x3 = TopLeftX + Center;
  int y3 = y1;
  
  int x4 = x3;
  int y4 = TopLeftY + Height;
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
 
  return x2;
 }
 
 if( Letter == 'S' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.25*Height;
  
  double x2 = x1;
  double y2 = TopLeftY + 0.75*Height;
  
  DrawArc( Image, x1, y1 , 0.25*Height, 1.5707963267948 , 6.28318530717 , Color );
  DrawArc( Image, x2, y2 , 0.25*Height, -1.5707963267948 ,3.1415926535897 , Color );
  
  return ebmpRound( TopLeftX + 0.5*Height );
 }
 
 if( Letter == 'U' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY + Height - Center;
  
  int x2 = x1;
  int y2 = TopLeftY; 
  
  int x3 = TopLeftX + Width;
  int y3 = y2;
  
  int x4 = x3;
  int y4 = y1;

  // centers of the circle
  
  double x5 = TopLeftX + Center;
  double y5 = TopLeftY + Height - Center; 
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  
  DrawArc( Image, x5, y5 , Center , 0 , 3.14159265358979 , Color ); 

  return x3; 
 }

 if( Letter == 'V' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = TopLeftX + Width;
  int y2 = y1;
  
  int x3 = TopLeftX + Center;
  int y3 = TopLeftY + Height;
  
  DrawLine( Image , x1, y1, x3, y3, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );

  return x2;
 } 
 
 if( Letter == 'W' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = ebmpRound(TopLeftX + 0.4*Height);
  int y2 = y1;
  
  int x3 = ebmpRound( TopLeftX + 0.8*Height);
  int y3 = y1;
  
  int x4 = ebmpRound( TopLeftX + 0.2*Height );
  int y4 = TopLeftY + Height;
  
  int x5 = ebmpRound( TopLeftX + 0.6*Height );
  int y5 = y4;
  
  DrawLine( Image , x1, y1, x4, y4, Color );
  DrawLine( Image , x4, y4, x2, y2, Color );
  DrawLine( Image , x2, y2, x5, y5, Color );
  DrawLine( Image , x5, y5, x3, y3, Color );

  return x3;
 }  
 
 if( Letter == 'X' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = TopLeftX + Width;
  int y2 = y1;
  
  int x3 = x1;
  int y3 = TopLeftY + Height;
  
  int x4 = x2;
  int y4 = y3;
  
  DrawLine( Image , x1 , y1, x4, y4 , Color );
  DrawLine( Image , x2 , y2, x3, y3 , Color );
 
  return x2;
 }
 
 if( Letter == 'Y' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = TopLeftX + Width;
  int y2 = y1;
  
  int x3 = TopLeftX + Center;
  int y3 = ebmpRound( TopLeftY + 0.5*Height);
  
  int x4 = x3;
  int y4 = TopLeftY + Height;
  
  DrawLine( Image , x1, y1, x3, y3, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );

  return x2;
 }
 
 if( Letter == 'Z' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = TopLeftX + Width;
  int y2 = y1;
  
  int x3 = x1;
  int y3 = TopLeftY + Height;
  
  int x4 = x2;
  int y4 = y3;

  
  DrawLine( Image , x1 , y1, x2, y2 , Color );
  DrawLine( Image , x2 , y2, x3, y3 , Color );
  DrawLine( Image , x3 , y3, x4, y4 , Color );
 
  return x2;
 } 
 
 // space 
 
 if( Letter == ' ' || Letter == '\t' )
 {
  return ebmpRound( TopLeftX + 0.5*Height );
 }

 // numbers

 if( Letter == '0' || Letter == 'O' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY + Height - Center;
  
  int x2 = x1;
  int y2 = TopLeftY + Center; 
  
  int x3 = TopLeftX + Width;
  int y3 = y2;
  
  int x4 = x3;
  int y4 = y1;

  // centers of the circles
  
  double x5 = TopLeftX + Center; 
  double y5 = TopLeftY + Center; 

  double x6 = x5;
  double y6 = TopLeftY + Height - Center; 
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  
  DrawArc( Image, x5, y5 , Center , 3.14159265358979 , 6.28318530717959 , Color ); 
  DrawArc( Image, x6, y6 , Center , 0 ,  3.14159265358979 , Color ); 
  
  return x3; 
 }
 
 if( Letter == '1' )
 {
  int x1 = ebmpRound( TopLeftX + Height*0.05);
  int y1 = TopLeftY+Height;
  
  int x2 = ebmpRound(x1 + 0.4*Height);
  int y2 = y1;
  
  int x3 = ebmpRound( x1 + 0.2*Height);
  int y3 = y1;
  
  int x4 = x3;
  int y4 = TopLeftY;
  
  int x5 = ebmpRound(x1 + 0.05*Height);
  int y5 = ebmpRound(TopLeftY+ 0.2*Height);
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  DrawLine( Image , x4, y4, x5, y5, Color );
  
  return ebmpRound(x2 + Height*0.05);
 } 
 
 if( Letter == '2' )
 {
  int x1 = TopLeftX + Width; // ebmpRound( TopLeftX + 0.6*Height );
  int y1 = TopLeftY+Height;
  
  int x2 = TopLeftX;
  int y2 = y1;
  
  int x3 = x1;
  int y3 = TopLeftY + Center; // ebmpRound( TopLeftY + 0.3*Height )+1;
  
  double x4 = TopLeftX + Center; // TopLeftX + (0.3*Height);
  double y4 = TopLeftY + Center; // TopLeftY + (0.3*Height);
  
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
  
  DrawArc( Image , x4 , y4 , Center , 2.74 , 6.3 , Color );
  
  return x1;
 } 
 
 if( Letter == '3' )
 {
  double x1 = TopLeftX + (0.25*Height);
  double y1 = TopLeftY + (0.25*Height);
  
  double x2 = x1;
  double y2 = TopLeftY + (0.75*Height);
  
  int x3 = ebmpRound( TopLeftX + 0.3*Height);
  int y3 = ebmpRound( TopLeftY + 0.5*Height);
  
  int x4 = ebmpRound( TopLeftX + 0.2*Height);
  int y4 = y3;
  
  DrawArc( Image , x1 , y1 , 0.25*Height , -3.14159265358979 , 1.57079632679490 , Color );
  DrawArc( Image , x2 , y2 , 0.25*Height , -1.57079632679490 , 3.14159265358979 , Color );
  DrawLine( Image , x3, y3, x4, y4, Color );

  return ebmpRound(TopLeftX + 0.5*Height); 
 }  
 
 if( Letter == '4' )
 {
  // define some control points
  
  int x1 = TopLeftX+Width;
  int y1 = TopLeftY+ebmpRound(Height*2.0/3.0);
  
  int x2 = TopLeftX;
  int y2 = y1;
  
  int x3 = ebmpRound( TopLeftX + 0.5*Height );
  int y3 = TopLeftY;
  
  int x4 = x3;
  int y4 = TopLeftY + Height;
  
 
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  
  return x1;
 }
 
 if( Letter == '5' )
 {
  int x1 = TopLeftX + Width;
  int y1 = TopLeftY;
  
  int x2;
  int y2 = TopLeftY;
  
  int x3 = TopLeftX + ebmpRound( 0.2*Height )-1;
  int y3 = TopLeftY + ebmpRound( 0.48786796564404*Height );
  
  x2 = x3+1;
  
  double x4 = TopLeftX + Center;
  double y4 = TopLeftY + Height - Center;

  DrawArc( Image , x4, y4, Center, -2.35619449019234 , 3 , Color );
 
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
 
  return x1;
 }

 if( Letter == '6' )
 {
  double x1 = TopLeftX + (0.25*Height);
  double y1 = TopLeftY + (0.25*Height);
  
  double x2 = x1;
  double y2 = TopLeftY + (0.75*Height);
  
  int x3 = TopLeftX;
  int y3 = ebmpRound( y1 );
  
  int x4 = x3;
  int y4 = ebmpRound( y2 );

  DrawArc( Image , x1 , y1 , 0.25*Height , 3.1 , 6.2 , Color );
  DrawArc( Image , x2 , y2 , 0.25*Height , 0 , 6.29 , Color );
  
  DrawLine( Image , x3, y3, x4, y4, Color );

  return TopLeftX + (int) ebmpRound(.5*Height); 
 } 
 
 if( Letter == '7' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = TopLeftX + Width;
  int y2 = y1;
  
  int x3 = ebmpRound(TopLeftX + 0.1*Height);
  int y3 = TopLeftY + Height;
 
  DrawLine( Image , x1, y1, x2, y2, Color );
  DrawLine( Image , x2, y2, x3, y3, Color );
  
  return x2; 
 }
 
 if( Letter == '8' )
 {
  double x1 = TopLeftX + (0.25*Height);
  double y1 = TopLeftY + (0.25*Height);
  
  double x2 = x1;
  double y2 = TopLeftY + (0.75*Height);

  DrawArc( Image , x1 , y1 , 0.25*Height , 0 , 6.28318530717959 , Color );
  DrawArc( Image , x2 , y2 , 0.25*Height , 0 , 6.28318530717959 , Color );

  return TopLeftX + (int) ebmpRound(.5*Height); 
 } 

 if( Letter == '9' )
 {
  double x1 = TopLeftX + (0.25*Height);
  double y1 = TopLeftY + (0.25*Height);
  
  double x2 = x1;
  double y2 = TopLeftY + (0.75*Height);
  
  int x3 = ebmpRound( TopLeftX + 0.5*Height );
  int y3 = ebmpRound( y1 );
  
  int x4 = x3;
  int y4 = ebmpRound( y2 );

  DrawArc( Image , x1 , y1 , 0.25*Height , 0 , 6.28318530717959 , Color );
  DrawArc( Image , x2 , y2 , 0.25*Height , 0 , 3 , Color );
  
  DrawLine( Image , x3, y3, x4, y4, Color );

  return TopLeftX + (int) ebmpRound(.5*Height); 
 } 
 
 if( Letter == '.' )
 {
  double x1 = TopLeftX + 1.25;
  double y1 = TopLeftY + Height  - 0.5;
 
  DrawArc( Image, x1, y1, 0.75 , 0 , 6.3 , Color );
  
  return ebmpRound( x1 + 1.25 );
 }
 
 if( Letter == '!' )
 {
  double x1 = TopLeftX + 1.25;
  double y1 = TopLeftY + Height  - 0.5;
  
  int x2 = ebmpRound( x1 );
  int y2 = TopLeftY;
  
  int x3 = x2;
  int y3 = ebmpRound( y1 - 2 );
  
  int y4 = ebmpRound( 0.05*(13*y3+7*y2) );
 
  DrawArc( Image, x1, y1, 0.75 , 0 , 6.3 , Color );
  
  DrawLine( Image, x2,y2, x3,y3 , Color);
  DrawLine( Image, x2-1, y2, x3-1,y4 , Color);
  
  return ebmpRound( x1 + 1.25 );
 } 
 
 if( Letter == ',' )
 {
  double x1 = TopLeftX + 1.25;
  double y1 = TopLeftY + Height  - 0.5;
  
  double x3 = x1;
  double y3 = y1 + 1.75;
 
  DrawArc( Image, x1, y1, 0.75 , 0 , 6.3 , Color );
  DrawArc( Image, x3, y3, 1.75 , -0.5*pi , 0.65*pi , Color );
  
  return ebmpRound( x1 + 1.25 );
 }
 
 if( Letter == '\'' )
 {
  double x1 = TopLeftX + 1.25;
  double y1 = TopLeftY + Center  - 0.5;
  
  double x3 = x1;
  double y3 = y1 + 1.75;
 
  DrawArc( Image, x1, y1, 0.75 , 0 , 6.3 , Color );
  DrawArc( Image, x3, y3, 1.75 , -0.5*pi , 0.65*pi , Color );
  
  return ebmpRound( x1 + 1.25 );
 } 

 if( Letter == '`' )
 {
  double x1 = TopLeftX + 1.25;
  double y1 = TopLeftY + Center  - 0.5;
  
  double x3 = x1;
  double y3 = y1 + 1.75;
 
  DrawArc( Image, x1, y1, 0.75 , 0 , 6.3 , Color );
  DrawArc( Image, x3, y3, 1.75 , 0.35*pi , 1.5*pi , Color );
  
  return ebmpRound( x1 + 1.25 );
 } 
 
 
 if( Letter == '"' )
 {
  double x1 = TopLeftX + 1.25;
  double y1 = TopLeftY + Center  - 0.5;
  
  double x3 = x1;
  double y3 = y1 + 1.75;
 
  DrawArc( Image, x1, y1, 0.75 , 0 , 6.3 , Color );
  DrawArc( Image, x3, y3, 1.75 , -0.5*pi , 0.65*pi , Color );
  
  DrawArc( Image, x1+3.5, y1, 0.75 , 0 , 6.3 , Color );
  DrawArc( Image, x3+3.5, y3, 1.75 , -0.5*pi , 0.65*pi , Color );  
  
  return ebmpRound( x1 + 1.25 + 3.5);
 }  
 
 if( Letter == '[' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = y1 + Height;
  
  int x3 = ebmpRound(TopLeftX + 0.15*Height)+1;
  int y3 = y1;
  
  int x4 = x3;
  int y4 = y2;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x1,y1,x3,y3,Color);
  DrawLine(Image,x2,y2,x4,y4,Color);
  
  return x3;
 }   
 
 if( Letter == ']' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = y1 + Height;
  
  int x3 = ebmpRound(TopLeftX + 0.15*Height)+1;
  int y3 = y1;
  
  int x4 = x3;
  int y4 = y2;
  
  DrawLine(Image,x3,y3,x4,y4,Color);
  DrawLine(Image,x1,y1,x3,y3,Color);
  DrawLine(Image,x2,y2,x4,y4,Color);
  
  return x3;
 }   
 
 if( Letter == '|' || Letter == 'l' )
 {
  int x1 = TopLeftX+2;
  int y1 = TopLeftY;
  
  int x2 = x1;
  int y2 = y1 + Height;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  
  return x1+2;
 }    
 
 if( Letter == ':' )
 {
  double x1 = TopLeftX + 1.25;
  double y1 = TopLeftY + Height  - 0.5;
  
  double x2 = x1;
  double y2 = TopLeftY + 0.5*Height;
 
  DrawArc( Image, x1, y1, 0.75 , 0 , 6.3 , Color );
  DrawArc( Image, x2, y2, 0.75 , 0 , 6.3 , Color );
  
  return ebmpRound( x1 + 1.25 );
 } 

 if( Letter == ';' )
 {
  double x1 = TopLeftX + 1.25;
  double y1 = TopLeftY + Height  - 0.5;
  
  double x2 = x1;
  double y2 = TopLeftY + 0.5*Height;
  
  double x3 = x1;
  double y3 = y1 + 1.75;
 
  DrawArc( Image, x1, y1, 0.75 , 0 , 6.3 , Color );
  DrawArc( Image, x2, y2, 0.75 , 0 , 6.3 , Color );
  DrawArc( Image, x3, y3, 1.75 , -0.5*pi , 0.65*pi , Color );
  
  return ebmpRound( x1 + 1.25 );
 } 
 
 if( Letter == '-' )
 {
  int TempWidth = ebmpRound(0.5*Height);
  if( TempWidth % 2 != 0 )
  { TempWidth++; }
  //int TempRad = (TempWidth-1)/2;
 
  int x1 = TopLeftX;
  int y1 = TopLeftY + TempWidth;
  
  int x2 = TopLeftX + TempWidth;
  int y2 = y1;
  
  DrawLine( Image, x1, y1, x2, y2 , Color );
  
  return x2;
 } 
 
 if( Letter == '=' )
 {
  int TempWidth = ebmpRound(0.5*Height);
  if( TempWidth % 2 != 0 )
  { TempWidth++; }
  //int TempRad = (TempWidth-1)/2;
 
  int x1 = TopLeftX;
  int y1 = TopLeftY + TempWidth-1;
  
  int x2 = TopLeftX + TempWidth+1;
  int y2 = y1;
  
  int x3 = x1;
  int y3 = y1+3;
  
  int x4 = x2;
  int y4 = y3;
  
  
  DrawLine( Image, x1, y1, x2, y2 , Color );
  DrawLine( Image, x3, y3, x4, y4 , Color );
  
  return x2;
 }  
 
 if( Letter == '+' )
 {
  int TempWidth = ebmpRound(0.5*Height);
  if( TempWidth % 2 != 0 )
  { TempWidth++; }
  int TempRad = (TempWidth-1)/2;
 
  int x1 = TopLeftX;
  int y1 = TopLeftY + TempWidth;
  
  int x2 = TopLeftX + TempWidth;
  int y2 = y1;
  
  int x3 = ( x1 + TempRad + 1);
  int y3 = ( y1 + TempRad + 1);

  int x4 = x3;
  int y4 = ( y1 - TempRad - 1);
  
  DrawLine( Image, x1, y1, x2, y2 , Color );
  DrawLine( Image, x3, y3, x4, y4 , Color );
  
  return x2;
 }  
 
 if( Letter == '/' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY+Height;
 
  int x2 = TopLeftX+Width;
  int y2 = TopLeftY;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
 
  return x2;
 }
 if( Letter == '\\' )
 {
  int x1 = TopLeftX+Width;
  int y1 = TopLeftY+Height;
 
  int x2 = TopLeftX;
  int y2 = TopLeftY;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
 
  return x1;
 }
 
 if( Letter == '%' )
 {
  int x1 = TopLeftX;
  int y1 = TopLeftY+Height;
 
  int x2 = TopLeftX+Width;
  int y2 = TopLeftY;
  
  double x3 = TopLeftX + 0.15*Height;
  double y3 = TopLeftY + 0.15*Height;
  
  double x4 = ceil( TopLeftX + 0.45*Height + 0.5);
  double y4 = ceil( TopLeftY + 0.85*Height );
  
  DrawLine(Image,x1,y1,x2,y2,Color);

  DrawArc(Image,x3,y3,0.15*Height,0,2*pi,Color);
  DrawArc(Image,x4,y4,0.15*Height,0,2*pi,Color);
  
  return x2;
 } 
 
 if( Letter == '_' )
 {
  DrawLine(Image,TopLeftX,TopLeftY+Height,TopLeftX+Width,TopLeftY+Height,Color);
 
  return TopLeftX + Width;
 }
 
 if( Letter == '^' )
 {
  DrawLine(Image,TopLeftX,TopLeftY+Center,TopLeftX+Center,TopLeftY,Color);
  DrawLine(Image,TopLeftX+Center,TopLeftY,TopLeftX+Width,TopLeftY+Center,Color);
 
  return TopLeftX + Width;
 } 
 
 if( Letter == '<' )
 {
  int x1 = TopLeftX;
  int y1 = ebmpRound( TopLeftY + 0.5*Height );
  
  int x2 = TopLeftX+Width;
  int y2 = TopLeftY;
  
  int x3 = x2;
  int y3 = TopLeftY+Height;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x1,y1,x3,y3,Color);
  
  return x2;
 }
 
 if( Letter == '>' )
 {
  int x1 = TopLeftX+Width;
  int y1 = ebmpRound( TopLeftY + 0.5*Height );
  
  int x2 = TopLeftX;
  int y2 = TopLeftY;
  
  int x3 = x2;
  int y3 = TopLeftY+Height;
  
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x1,y1,x3,y3,Color);
  
  return x1;
 } 
 
 if( Letter == '#' )
 {
  int TempWidth = ebmpRound(0.5*Height);
  if( TempWidth % 2 != 0 )
  { TempWidth++; }
  //int TempRad = (TempWidth-1)/2;
 
  int x1 = TopLeftX;
  int y1 = (int) floor(TopLeftY + 0.5*Height-1);
  
  int x2 = TopLeftX + Width;
  int y2 = y1;
  
  int x3 = x1;
  int y3 = y1+2;
  
  int x4 = x2;
  int y4 = y3;
  
  int x5 = TopLeftX+Center-1;
  int y5 = TopLeftY;

  int x6 = x5;
  int y6 = TopLeftY+Height;
  
  int x7 = TopLeftX+Center+1;
  int y7 = TopLeftY;

  int x8 = x7;
  int y8 = TopLeftY+Height;
  
  DrawLine( Image, x1, y1, x2, y2 , Color );
  DrawLine( Image, x3, y3, x4, y4 , Color );
  DrawLine( Image, x5, y5, x6, y6, Color );
  DrawLine( Image, x7,y7,x8,y8,Color);

  return x2;
 }
 
 if( Letter == '?' )
 {
  double x1 = TopLeftX+Center;
  double y1 = TopLeftY+Center;
  
  int x2 = (int) x1;
  int y2 = TopLeftY + Width;
  
  int x3 = x2;
  int y3 = ebmpRound(TopLeftY+ 0.8*Height);
  if( TopLeftY+Height-y3 <= 2 )
  { y3--; }
  
  double x4 = x1;
  double y4 = TopLeftY + Height  - 0.5;
  
  DrawArc(Image,x1,y1,Center,pi,pi/2,Color);
  DrawLine(Image,x2,y2,x3,y3,Color);
  DrawArc( Image, x4, y4, 0.75 , 0 , 6.3 , Color );
 
  return TopLeftX + Width;
 }
 
 if( Letter == '*' )
 {
  int x1 = TopLeftX+Center;
  int y1 = TopLeftY;
 
  int x2 = x1;
  int y2 = TopLeftY+Height;
  
  int x3 = TopLeftX;
  int y3 = ebmpRound(TopLeftY+0.5*Height);
  
  int x4 = TopLeftX+Width;
  int y4 = y3;
  
  int x5 = TopLeftX+1; // ebmpRound(TopLeftX+0.15*Width);
  int y5 = TopLeftY+1; // ebmpRound(TopLeftY+0.15*Height);
  
  int x6 = TopLeftX+Width-1; // ebmpRound(TopLeftX+0.45*Width);
  int y6 = TopLeftY+Height-1; //  ebmpRound(TopLeftY+0.85*Height);
  
  int x7 = x6;
  int y7 = y5;
  
  int x8 = x5;
  int y8 = y6;
 
  DrawLine(Image,x1,y1,x2,y2,Color);
  DrawLine(Image,x3,y3,x4,y4,Color);
  DrawLine(Image,x5,y5,x6,y6,Color);
  DrawLine(Image,x7,y7,x8,y8,Color);
  
  return x4;
 }
 
 if( Letter == '@' )
 {
  double x1 = TopLeftX + 1.5*Center;
  double y1 = TopLeftY + Height - 1.5*Center;
  
  double x2 = x1 + .35*Center + .6*Center;
  double y2 = y1 + .35*Center;
  
  DrawArc(Image,x1,y1,Center*1.5,0,2*pi,Color);
  DrawArc(Image,x1,y1,Center*0.5,0,2*pi,Color);
  
  DrawArc(Image,x2,y2,Center*0.45,0,pi,Color);
 
  return ebmpRound(TopLeftX + 3*Center);
 }
 
 if( Letter == '~' )
 {
  double x1 = TopLeftX + 0.2*Height;
  double y1 = TopLeftY + 0.4*Height;
  
  double x2 = TopLeftX + 0.6*Height;
  double y2 = y1;
  
  DrawArc(Image,x1,y1,0.2*Height, 0.7*pi,2*pi, Color);
  DrawArc(Image,x2,y2,0.2*Height, -0.3*pi,pi, Color);
 
  return ebmpRound(TopLeftX + 0.8*Height);
 }
 
 if( Letter == '(' ) 
 {
  double x5 = TopLeftX + Center; 
  double y5 = TopLeftY + 0.5*Height; 

  DrawArc( Image, x5, y5 , 0.7*Height , 0.5*pi , -0.5*pi , Color ); 
 
  return TopLeftX;
 }
 
 if( Letter == ')' ) 
 {
  double x5 = TopLeftX - Center; 
  double y5 = TopLeftY + 0.5*Height; 

  DrawArc( Image, x5, y5 , 0.7*Height , -0.5*pi , 0.5*pi , Color ); 
 
  return TopLeftX;
 } 
 
 if( Letter == '&' )
 {
  double x1 = TopLeftX + Center;
  double y1 = TopLeftY + Height-Center;
  
  double x2 = x1;
  double y2 = TopLeftY + 0.2*Height;
  
  //int x3 = ebmpRound(TopLeftX+0.5*Height);
  //int y3 = ebmpRound(y2);
  
  //int x4 = TopLeftX;
  //int y4 = ebmpRound(y1);
  
  int x5 = ebmpRound(TopLeftX+0.25*Height);
  int y5 = TopLeftY+Height-2*Center;
  
  int x6 = ebmpRound(TopLeftX+1.1*Width);
  int y6 = TopLeftY+Height;  
  
  
  DrawArc( Image, x1,y1, Center, -.1*pi, 1.5*pi, Color);
  DrawArc( Image, x2,y2, 0.2*Height, 0,2*pi,Color); 
  
//  DrawLine( Image, x3,y3, x4,y4, Color);
  DrawLine( Image, x5,y5, x6,y6, Color);
 
  return x6;
 }

 if( Letter == '&' && 1 == 0 ) // alt ampersand &
 {
  double x1 = TopLeftX + Center;
  double y1 = TopLeftY + Height-Center;
  
  double x2 = x1;
  double y2 = TopLeftY + 0.2*Height;
  
  int x3 = ebmpRound(TopLeftX+0.5*Height);
  int y3 = ebmpRound(y2);
  
  int x4 = TopLeftX;
  int y4 = ebmpRound(y1);
  
  int x5 = ebmpRound(TopLeftX+0.1*Height);
  int y5 = y3;
  
  int x6 = ebmpRound(TopLeftX+1.1*Width);
  int y6 = TopLeftY+Height;  
  
  
  DrawArc( Image, x1,y1, Center, -.25*pi, pi, Color);
  DrawArc( Image, x2,y2, 0.2*Height, pi,2*pi,Color); 
  
  DrawLine( Image, x3,y3, x4,y4, Color);
  DrawLine( Image, x5,y5, x6,y6, Color);
 
  return x6;
 } 
 
 if( Letter == '$' )
 {
  double x1 = TopLeftX + 0.25*Height;
  double y1 = TopLeftY + 0.25*Height;
  
  double x2 = x1;
  double y2 = TopLeftY + 0.75*Height;
  
  int x3 = ebmpRound(x1);
  int y3 = ebmpRound(TopLeftY-0.1*Height);
  
  int x4 = x3;
  int y4 = ebmpRound(TopLeftY+1.1*Height);
  
  DrawArc( Image, x1, y1 , 0.25*Height, 1.5707963267948 , 6.28318530717 , Color );
  DrawArc( Image, x2, y2 , 0.25*Height, -1.5707963267948 ,3.1415926535897 , Color );
  DrawLine( Image, x3, y3, x4, y4, Color);
  
  return ebmpRound( TopLeftX + 0.5*Height );
 }
 
 if( Letter ==  '}' )
 {
  double x1 = TopLeftX;
  double y1 = TopLeftY + 0.15*Height;
  
  double x2 = x1+0.3*Height;
  double y2 = TopLeftY + 0.4*Height;

  double x3 = x2;
  double y3 = TopLeftY + 0.6*Height;
  
  double x4 = x1;
  double y4 = TopLeftY + 0.85*Height;
  
  DrawArc( Image, x1,y1, 0.2*Height, 1.5*pi, 2*pi, Color);
  
  DrawArc( Image, x2,y2, 0.1*Height, 0.5*pi,pi, Color);
  DrawArc( Image, x3,y3, 0.1*Height, pi,1.5*pi, Color);
  
  DrawArc( Image, x4,y4, 0.2*Height, 0,0.5*pi, Color);
  
  int x5 = ebmpRound( TopLeftX+0.2*Height);
  int y5 = ebmpRound( TopLeftY+0.15*Height);
  
  int x6 = x5;
  int y6 = ebmpRound( TopLeftY+0.4*Height);
  
  DrawLine( Image, x5,y5, x6,y6, Color );

  int x7 = x5;
  int y7 = ebmpRound( TopLeftY+0.6*Height);
  
  int x8 = x7;
  int y8 = ebmpRound( TopLeftY+0.85*Height);
  
  DrawLine( Image, x7,y7, x8,y8, Color );  

  return ebmpRound(TopLeftX + 0.4*Height);
 }
 
 if( Letter ==  '{' )
 {
  double x1 = TopLeftX + 0.3*Height;
  double y1 = TopLeftY + 0.15*Height;
  
  double x2 = TopLeftX  ;
  double y2 = TopLeftY + 0.4*Height;

  double x3 = x2;
  double y3 = TopLeftY + 0.6*Height;
  
  double x4 = x1;
  double y4 = TopLeftY + 0.85*Height;
  
  DrawArc( Image, x1,y1, 0.2*Height, pi,1.5*pi, Color);
  
  DrawArc( Image, x2,y2, 0.1*Height, 0,0.5*pi, Color);
  DrawArc( Image, x3,y3, 0.1*Height, 1.5*pi,2*pi, Color);
  
  DrawArc( Image, x4,y4, 0.2*Height, 0.5*pi,pi, Color);
  
  int x5 = ebmpRound( TopLeftX+0.1*Height);
  int y5 = ebmpRound( TopLeftY+0.15*Height);
  
  int x6 = x5;
  int y6 = ebmpRound( TopLeftY+0.4*Height);
  
  DrawLine( Image, x5,y5, x6,y6, Color );

  int x7 = x5;
  int y7 = ebmpRound( TopLeftY+0.6*Height);
  
  int x8 = x7;
  int y8 = ebmpRound( TopLeftY+0.85*Height);
  
  DrawLine( Image, x7,y7, x8,y8, Color );  

  return ebmpRound(TopLeftX + 0.4*Height);
 }  
 
 if( Letter == '&' && 1 == 0 ) // old ampersand '&'
 {
  double x1 = TopLeftX + (0.25*Height);
  double y1 = TopLeftY + (0.25*Height);
  
  double x2 = x1;
  double y2 = TopLeftY + (0.75*Height);
  
  int x3 = ebmpRound( TopLeftX + 0.3*Height);
  int y3 = ebmpRound( TopLeftY + 0.5*Height);
  
  int x4 = ebmpRound( TopLeftX + 0.2*Height);
  int y4 = y3;
  
  int x5 = ebmpRound(TopLeftX + 0.35*Height);
  int y5 = ebmpRound(TopLeftY + 0.75*Height);
  
  int x6 = ebmpRound(TopLeftX + 0.65*Height);
  int y6 = y5;
  
  
  DrawArc( Image , x1 , y1 , 0.25*Height , 1.57079632679490 , 2*pi , Color );
  DrawArc( Image , x2 , y2 , 0.25*Height , 0, 1.5*pi , Color );
  DrawLine( Image , x3, y3, x4, y4, Color );
  DrawLine( Image , x5, y5, x6, y6, Color );

  return x6;
 }   
 
 
 return TopLeftX;
}

int PrintCopyright( BMP& Image, int TopLeftX, int TopLeftY , int Height , 
                  RGBApixel Color )
{
 double pi = 3.14159265358979;
 
 //int CharNumber = 0;
 int StartX = ebmpRound(TopLeftX+0.25*Height);
 int Spacing = (int) ebmpRound( 0.2*Height );
 if( Spacing < 3 )
 { Spacing = 3; }
 int StartY = ebmpRound( TopLeftY-0.25*Height);
 
 double x1 = TopLeftX + 0.5*Height;
 double y1 = TopLeftY + 0.5*Height;
 
 DrawArc(Image, x1, y1, 0.6*Height , 0, 2*pi , Color );
 return PrintLetter( Image, 'c' , StartX, StartY , Height, Color ) + Spacing; 
}