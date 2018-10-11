
int ReadINI()
{
   auto FILE *ini;
   auto char tm[MAX_PATH];

   ini = fopen( "Juego.INI", "rb" );

   if( ini == NULL )
   {
      sprintf( tm, "No existe el archivo %s.", "Juego.INI" );
      MessageBox( NULL, tm, "Error", 16 );
      return -1;
   }

   if( filesize( ini ) == 0 )
   {
      //sprintf( tm, "Archivo vacio: %s.", IniFile );
      //MessageBox( NULL, tm, szClassName, 16 );
      return -2;
   }

   ProcessINI( ini );
   fclose( ini );
   return ERROR_SUCCESS;
}//_____________________________________________________________________________

int ProcessINI( FILE *file )
{
   auto const char cComment[] = "#";
   auto const char cCR[] = "\r";
   auto const char cLF[] = "\n";
   auto const char cEnd[] = ";";
   auto const char cEqu[] = "=";
   auto const int MAX_BUF = 0xFF;
   auto const int MAX_VAR = 0xFF;

   auto char buff[MAX_BUF];
   auto char tmp[MAX_BUF];
   auto char value[MAX_BUF];
   auto char var[MAX_BUF];
   auto unsigned int L;
   auto bool is_value = false;
   auto bool bCmt = false;
   auto int X;

   L = filesize( file );

   for( X = 1; X < L + 1; X += 1 )
   {
      fread( buff, 1, 1, file );
//////////////////////////////////// CMT ///////////////////////////////////////
      if(( bCmt ) || ( !strcmp( buff, cComment )) || (( strlen( tmp )) >= MAX_VAR ))
      {
         bCmt = true;
         if( (!strcmp( buff, cCR )) || ( X == L ) || ( !strcmp( buff, cLF )))
         {
            bCmt = false;
         }
      }
//////////////////////////  IS_VAR ( not is_value )  ///////////////////////////
      else if( !is_value )
      {
         if(( !strcmp( buff, cCR ))
            || ( !strcmp( buff, cLF ))
            || ( !strcmp( buff, cEnd )))
         {
            ProcessVar( tmp, "" );
            sprintf( tmp, "" );
         }

         if(( !strcmp( buff, cEqu )) && ( tmp != "" ))
         {
            is_value = true;
            strcpy( var, tmp );
            sprintf( tmp, "" );
         }
         else if( strcmp( buff, cCR ))
         {
            if( strcmp( buff, cLF ))
            {
               if( strcmp( buff, " " ))
               {
                  if( strcmp( buff, "\t" ))
                  {
                     if( strcmp( buff, cEnd ))
                     {
                        sprintf( tmp, "%s%s", tmp, buff );
                     }
                  }
               }
            }
         }
      }
///////////////////////////////////  IS_VALUE  /////////////////////////////////
      else if( is_value )
      {
         if(( !strcmp( buff, cCR ))
            || ( !strcmp( buff, cLF ))
            || ( X == L )
            || ( !strcmp( buff, cComment ))
            || ( !strcmp( buff, cEnd )))
         {
            if( strcmp( buff, cCR ))
            {
               if( strcmp( buff, cLF ))
               {
                  if( strcmp( buff, cEnd ))
                  {
                     sprintf( tmp, "%s%s", tmp, buff );
                  }
               }
            }
            is_value = false;
            strcpy( value, tmp );
            sprintf( tmp, "" );
            //#ifdef DEBUG
               MessageBox( hWnd, value, var, 64 );
            //#endif
            ProcessVar( var, value );
         }
         else
         {
            sprintf( tmp, "%s%s", tmp, buff );
         }
      }
   }
   return ERROR_SUCCESS;
}//_____________________________________________________________________________
