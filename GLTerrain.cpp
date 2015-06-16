#include "stdafx.h"
#include "GLTerrain.h"
#include <cstdio>

#include "cv.h"
#include "highgui.h"  

#include <opencv2/opencv.hpp>
//opencv内存泄漏原因与MFC动态库冲突
//设置工程为在静态库中使用MFC，或延迟加载CV的动态库（？）
using namespace cv;
using namespace std;
#include <cassert>

#define SCALE_FACTOR  1
#define MAX_HEIGHT    30
GLTerrain::GLTerrain()
{
	m_scale=1.0f;
	m_hmap=NULL;
	m_grassTexture = m_waterTexture = 0;
	m_Width=260;
	m_Height=260;
}
GLTerrain::~GLTerrain()
{
	if(m_hmap)
	{
		delete []m_hmap;
		m_hmap=NULL;
	}
	if(m_grassTexture!=0)
		glDeleteTextures(1, &m_grassTexture);
	if(m_waterTexture!=0)
		glDeleteTextures(1, &m_waterTexture);
}
int GLTerrain::LoadTexture2()
{
	//Mat img;

	
	/*img=imread("F:\\a神州泰岳\\3d\\other\\BingChuan\\debug\\rgb.jpg",-1);
	ASSERT(img.data!=NULL);
	m_texWidth = img.cols;
	m_texHeight = img.rows;

	glGenTextures(1, &m_grassTexture);
	glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_texWidth, m_texHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, img.data);
*/
	return 0;
}
int GLTerrain::LoadTexture()
{
	//MFC的DLL与OpenCV冲突造成内存泄漏，改为静态库中使用MFC或延时加载OpenCV的DLL库
	IplImage* image=cvLoadImage("F:\\a神州泰岳\\3d\\other\\BingChuan\\debug\\rgb.jpg",-1);
	IplImage* image2=cvLoadImage("F:\\a神州泰岳\\3d\\other\\BingChuan\\debug\\dj.jpg",-1);
	assert(image!=NULL);
	assert(image2!=NULL);
	m_texWidth = image->width;
	m_texHeight = image->height;
	int nchannel = image->nChannels;
	int nsize = image->imageSize;
	unsigned char *imagedata =new unsigned char[nsize];
	memcpy(imagedata,image->imageData,sizeof(unsigned char)*image->imageSize);
	glGenTextures(1, &m_grassTexture);
	glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_texWidth, m_texHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imagedata);
	ASSERT(image->imageSize==image2->imageSize);//确保两张图大小一致
	memcpy(imagedata,image2->imageData,sizeof(unsigned char)*image2->imageSize);
	glGenTextures(1, &m_waterTexture);
	glBindTexture(GL_TEXTURE_2D, m_waterTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_texWidth, m_texHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, imagedata);


	delete[] imagedata;
	imagedata = NULL;
	
	cvReleaseImage(&image);
	cvReleaseImage(&image2);
	image = NULL;
	image2 = NULL;
	//unsigned char *imagedata = new unsigned char[nsize];
	//memcpy(imagedata,image->imageData,sizeof(unsigned char)*image->imageSize);
	//glGenTextures(1, &m_grassTexture);
	//glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	//多重纹理贴图函数
	//gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image.GetWidth(), image.GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.GetImage());
	return 0;


}
int GLTerrain::Init(int width,int height)
{
	m_Width=width;
	m_Height=height;
	LoadTexture();
	//CreateMesh();
	CreateRawMesh();
	InitSettings();
	return 0;
}
void GLTerrain::InitSettings()
{
	glClearColor(0.125f, 0.5f, 1.0f, 1.0f);//背景色蓝色
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	glBindTexture(GL_TEXTURE_2D, m_waterTexture);
	////缓冲区是自定义类型的数组
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, m_pVertexBuf);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glTexCoordPointer(2, GL_FLOAT, 0, m_pTextureBuf);
}
std::string GLTerrain::GetHDataFile()
{
	return "F:\\a神州泰岳\\3d\\other\\BingChuan\\debug\\rgb2602.raw";
}
int GLTerrain::CreateRawMesh()
{
	ASSERT(m_Width!=0);
	ASSERT(m_Height!=0);
	m_hmap=new unsigned char[m_Width * m_Height];
	FILE *fp =NULL;
	fopen_s(&fp,GetHDataFile().c_str(), "rb");
	//读取高度数据最大0.25   400*240
	//fread_s(m_hmap,nWidth*nHeight,nWidth*nHeight,1,fp);
	fread(m_hmap,1,m_Width*m_Height,fp);
	fclose(fp);
	return 0;
}
int GLTerrain::CreateMesh()
{
	int nWidth = 400;
	int nHeight = 240;
	float fWidth = 3.2;
	float fHeight = 1.744;


	float* pData =new float[ nWidth * nHeight];
	m_hmap=new unsigned char[nWidth * nHeight];
	FILE *fp =NULL;
	fopen_s(&fp,"F:\\a神州泰岳\\3d\\other\\BingChuan\\debug\\dem.txt", "r");
	int nIndex;	
	//读取高度数据最大0.25   400*240
	for(int row = 0; row < nHeight; row++)	
	{
		nIndex = row * nWidth;
		for (int col = 0; col < nWidth; col++)
		{
			fscanf_s(fp, "%f,", &pData[nIndex + col]);
			unsigned char tp=(unsigned char)(pData[nIndex+col]*50.0);
			m_hmap[nIndex+col]=tp;
		}
	}	
	fclose(fp);

	
	
	delete[] pData;
	pData = NULL;
	return 0;
}
void GLTerrain::DrawTerrainNet()
{
	if(m_hmap==NULL)
		return;
	//glLineWidth(1.0f);
	glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for (int z = 0; z <m_Height - 1; ++z)
	{
		//是否背景剔除
		//是否只绘制线条
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//添加此句是否绘制线条替代纹理
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x <m_Width; ++x)
		{	
			float height=m_hmap[z * m_Height + x];
			float nextheight=m_hmap[(z + 1)* m_Height  + x];
			glTexCoord2f((GLfloat)x/m_Width, (GLfloat)z/m_Height);
			glVertex3f(static_cast<GLfloat>(x)*m_scale, m_hmap[z * m_Height + x]*m_scale/10.0f, static_cast<GLfloat>(z*m_scale));
			glTexCoord2f((GLfloat)x/m_Width, (GLfloat)(z+1)/m_Height);
			glVertex3f(static_cast<GLfloat>(x)*m_scale, m_hmap[(z + 1)* m_Height  + x]*m_scale/10.0f, static_cast<GLfloat>((z + 1)*m_scale));
		}
		glEnd();
	}

}
int GLTerrain::DrawTerrain()
{
	if(m_hmap==NULL)
		return 0;
	//glLineWidth(1.0f);
	glBindTexture(GL_TEXTURE_2D, m_grassTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	for (int z = 0; z <m_Height - 1; ++z)
	{
		//是否背景剔除
		//是否只绘制线条
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//添加此句是否绘制线条替代纹理
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x <m_Width; ++x)
		{	
			float height=m_hmap[z * m_Height + x];
			float nextheight=m_hmap[(z + 1)* m_Height  + x];
			glTexCoord2f((GLfloat)x/m_Width, (GLfloat)z/m_Height);
			glVertex3f(static_cast<GLfloat>(x)*m_scale, m_hmap[z * m_Height + x]*m_scale/10.0f, static_cast<GLfloat>(z*m_scale));
			glTexCoord2f((GLfloat)x/m_Width, (GLfloat)(z+1)/m_Height);
			glVertex3f(static_cast<GLfloat>(x)*m_scale, m_hmap[(z + 1)* m_Height  + x]*m_scale/10.0f, static_cast<GLfloat>((z + 1)*m_scale));
		}
		glEnd();
	}
	return 0;
}