void CShelfView::draw_rect(int(*image)[256], int wid, int hei, int xloc, int yloc)
{
	int i, j;
	int inner = 60;
	int outer = 220;
	for (i = 0; i < wid; i++) {
		for (j = 0; j < hei; j++) {
			image[xloc + i][yloc + j] = outer;
		}
	}
	for (i = 0; i < wid + 1; i++) {
		image[xloc + i][yloc] = inner;
		image[xloc + i][yloc + hei] = inner;
	}
	for (i = 0; i < hei + 1; i++) {
		image[xloc][yloc + i] = inner;
		image[xloc + wid][yloc + i] = inner;
	}
}
void CShelfView::SortWidth(int* wid, int* hei, int size)
{
	int i, j;
	int tmp;
	for (i = 0; i < size; i++)
	{
		for (j = i; j < size; j++)
		{
			if (wid[i] < wid[i + j]) 
			{
				tmp = wid[i];
				wid[i] = wid[i + j];
				wid[i + j] = tmp;
				tmp = hei[i];
				hei[i] = hei[i + j];
				hei[i + j] = tmp;
			}
		}
	}
}
// CShelfView 그리기

void CShelfView::OnDraw(CDC* pDC)
{
	CShelfDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	unsigned char R, G, B;
	/*for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			int tmp = i * pDoc->m_InputImage[i* 256 + j];
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}*/
	int output_image[256][256];
	int i, j, q, tmp;
	int x_dart = 0;
	int y_dart = 0;
	int upp = 0;

	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			output_image[i][j] = 150;
		}
	}
	int width[] = { 11, 39, 13, 25, 20, 55, 54, 50, 16, 51, 27, 54, 13, 34, 48, 19, 18, 23, 39, 14, 31, 58, 24, 58, 57, 57, 28, 30, 18, 10, 42, 31, 13, 10, 57, 54, 50, 20, 31, 35, 25, 37, 32, 42, 37, 24, 44, 29, 25, 17, 55, 27, 23, 38, 15, 46, 24, 20, 33, 12, 31, 41, 25, 39, 12, 55, 35, 13, 22, 60, 28, 31, 27, 38, 19, 28, 24, 38, 11, 36, 27, 25, 16, 19, 32, 40, 33, 15, 23, 19, 42, 43, 10, 45, 15, 15, 33, 27, 53, 18 };
	int height[] = { 21, 43, 52, 35, 28, 66, 30, 61, 49, 60, 39, 62, 65, 50, 63, 41, 61, 51, 58, 35, 35, 67, 25, 63, 59, 69, 34, 61, 57, 26, 66, 50, 63, 42, 63, 61, 53, 54, 66, 48, 28, 54, 50, 49, 62, 31, 63, 66, 51, 52, 67, 48, 39, 41, 46, 68, 41, 38, 42, 12, 51, 53, 28, 69, 61, 59, 60, 60, 41, 68, 33, 60, 48, 60, 63, 50, 31, 42, 17, 50, 59, 42, 61, 35, 67, 53, 42, 40, 62, 42, 57, 59, 12, 68, 16, 34, 67, 54, 64, 22 };
	for (i = 0; i < sizeof(width) / 4; i++) {
		if (width[i] > height[i]) {
			tmp = width[i];
			width[i] = height[i];
			height[i] = tmp;
		}
	}
	SortWidth(width, height, sizeof(width) / 4);
	for (i = 0; i < sizeof(width)/4; i++) {
		if (y_dart + height[i] < 256) {
			if (x_dart + width[i] < 256) {
				draw_rect(output_image, width[i], height[i], x_dart, upp);
				x_dart += width[i];
				if (y_dart < height[i] + upp) {
					y_dart = upp + height[i];
				}
			}
			else {
				if (y_dart + height[i] > 256) {
					
					//break!!	
					continue;
				}
				upp = y_dart;
				for (q = 0; q < 256; q++) {
					output_image[q][upp] = 0;
				}
				x_dart = 0;
				draw_rect(output_image, width[i], height[i], x_dart, upp);
				if (y_dart < height[i] + upp) {
					y_dart = upp + height[i];
				}
				x_dart += width[i];

			}
		}
		else {
			
			//break!!
			continue;
		}
	}
	for (i = 0; i < 210; i++) {
		for (j = 0; j < 240; j++) {
			R = output_image[j][i];
			//R = pDoc->m_OutputImage[i * pDoc->m_width + j];
			G = B = R;
			pDC->SetPixel(j, i, RGB(R, G, B));
		}
	}

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}
