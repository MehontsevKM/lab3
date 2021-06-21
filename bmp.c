# define  _CRT_SECURE_NO_WARNINGS
# включить  < stdio.h >
# включить  < windows.h >
# определить  WIN32_MEAN_AND_LEAN
# включить  " bmp.h "

недействительное  чтение ( const  char * file_in, const  char * file_out) {
	
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	ФАЙЛ * вход, * выход;

	
	input = fopen ( " file_in.bmp " , " rb " );
	output = fopen ( " file_out.bmp " , " wb " );

	if (! input) {
		printf ( " Файл BMP не найден \ n " );
		система ( « пауза » );
		возврат ;
	}

	fread (& file_header, sizeof (BITMAPFILEHEADER), 1 , ввод);
	fread (& info_header, sizeof (BITMAPINFOHEADER), 1 , ввод);

	if (info_header. biCompression ! = 0 || info_header. biBitCount ! = 24 || info_header. biPlanes ! = 1 ) {
		printf ( " Файл не BMP24 \ n " );
		система ( « пауза » );
		возврат ;
	}
	out (заголовок_файла, заголовок_информации, ввод, вывод);
}

void  out (BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header, ФАЙЛ * вход, ФАЙЛ * выход) {
	RGBTRIPLE пиксель;
	int Ширина = info_header. biWidth ;
	int Высота = info_header. biHeight ;

	 заполнение беззнакового символа = 0 ;
	если ((Ширина * 3 )% 4 )
		padding = 4 - (Ширина * 3 )% 4 ;

	RGBTRIPLE ** img = malloc (Высота * sizeof (RGBTRIPLE));
	для ( size_t i = 0 ; i <Высота; i ++)
		img [i] = malloc (Ширина * sizeof (RGBTRIPLE));

	for ( int i = 0 ; i <Height; i ++) {
		for ( int j = 0 ; j <Ширина; j ++) {
			fread (& pixel, sizeof (RGBTRIPLE), 1 , input);
			img [i] [j] = пиксель;
		}
		fseek (ввод, заполнение, SEEK_CUR);
	}
	fclose (ввод);

	info_header. biHeight = Ширина;
	info_header. biWidth = Высота;
	fwrite (& file_header, sizeof (BITMAPFILEHEADER), 1 , вывод);
	fwrite (& info_header, sizeof (BITMAPINFOHEADER), 1 , вывод);

	заполнение = 0 ;
	если ((Высота * 3 )% 4 )
		padding = 4 - (Высота * 3 )% 4 ;

	for ( int j = Width - 1 ; j> = 0 ; j--) {
		для ( int i = 0 ; i <Высота; i ++)
			fwrite (& img [i] [j], sizeof (RGBTRIPLE), 1 , вывод);

		if (padding! = 0 ) {
			BYTE filler = 0 ;
			fwrite (& заполнитель, sizeof (BYTE), заполнение, вывод);
		}
	}

}
