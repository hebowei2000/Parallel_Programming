#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
	int mp = 500;
	double er = 2;
	double rs = 1000;
	String  p = "God's_fingerprint";
	for (int i = 1;i<argc;i = i + 2)
	{
		if (argv[i][0] == '-'&& (i + 1) < argc)
		{

			if (argv[i][1] == 'm'&&argv[i][2] == 'p'&&argv[i][3] == '\0')
				mp = atoi(argv[i + 1]);
			else if (argv[i][1] == 'e'&&argv[i][2] == 'r'&&argv[i][3] == '\0')
				er = atof(argv[i + 1]);
			else if (argv[i][1] == 'r'&&argv[i][2] == 's'&&argv[i][3] == '\0')
				rs = atoi(argv[i + 1]);
			else if (argv[i][1] == 'p'&&argv[i][2] == '\0')
				p = String(argv[i + 1]);
			else
			{
				cout << "Please give standard argv" << endl << "-mp£ºthe largest iteration times\n -er£ºiterative divergence bound\n -rs£ºresolution£¬smaller than 1\n-p£ºfile saving path" << endl;
				exit(1);
			}
		}
		else
		{
			cout << "Please give standard argv" << endl << "-mp£ºthe largest iteration times\n -er£ºiterative divergence bound\n -rs£ºresolution£¬smaller than 1\n-p£ºfile saving path" << endl;
			exit(1);
		}
	}
	int length = 4 * rs;
	double step = 1 / rs;
	Mat  img = Mat::zeros(Size(length, length), CV_8UC3);
	Mat  resized_img;
	int colorfront[3] = { 255,255,255 };
	int background[3] = { 0,0,255};
	cout << "**************************************" << endl;
	cout << "mp=" << mp << "\n er=" << er << "\n rs=" << rs << "\n path\"=" << p << ".jpg\"" << endl;
	cout << "Threads:" << omp_get_max_threads() << endl << "Drawing........\n";
	omp_set_num_threads(omp_get_max_threads() * 2 );
	for (int i = 0;i<length;i++)
	{
#pragma omp parallel for 
		for (int j = 0;j<length;j++)
		{
			 //use complex lib function
			complex<double> c{-2+((double)i)*step, -2+((double)j)*step};
			complex<double> z{0,0};
			int count=0;
			while(count<=mp&&abs(z)<=er)
			{
			z=z*z+c;
			count++;
			}
			
			/*// reconstruct the code without complex lib to improve code efficiency
			double ca = -2 + ((double)i)*step;double cb = -2 + ((double)j)*step;
			double za = 0;double zb = 0;
			double zaback;
			int count = 0;
			while (count <= mp && (za*za + zb * zb) <= er * er)
			{
				zaback = za * za - zb * zb + ca;
				zb = 2 * zb*za + cb;
				za = zaback;
				count++;
			}
			*/
			if (count>mp)
			{
				img.at<Vec3b>(j, i)[0] = background[0];
				img.at<Vec3b>(j, i)[1] = background[1];
				img.at<Vec3b>(j, i)[2] = background[2];
			}
			else
			{
				img.at<Vec3b>(j, i)[0] = colorfront[0];
				img.at<Vec3b>(j, i)[1] = colorfront[1];
				img.at<Vec3b>(j, i)[2] = colorfront[2];
			}
			//cout << "Running_Threads:" << omp_get_num_threads() << endl;
		}
	}
	
	imwrite(p + ".jpg", img);
	resize(img, resized_img, Size(img.cols / 5, img.rows / 5), 0, 0, INTER_LINEAR);
	imshow(p+".jpg", resized_img);
	waitKey(0);
	return 0;
}




