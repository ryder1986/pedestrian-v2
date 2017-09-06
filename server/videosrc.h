#ifndef VIDEOSRC_H
#define VIDEOSRC_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <QObject>
#include <QThread>
#include "common.h"
using namespace cv;
using namespace std;
//#include "videohandler.h"
class VideoSrc:public QObject{
    Q_OBJECT
public:

    VideoSrc()
    {
        video_connected_flag=true;
        //     p_cap= cvCreateFileCapture("rtsp://192.168.1.81:554");  //读取视频
        p_cap= cvCreateFileCapture("/root/repo-github/pedestrian/test.mp4");  //读取视频
    }
    VideoSrc(QString path)
    {
        //     p_cap= cvCreateFileCapture("rtsp://192.168.1.81:554");  //读取视频
        prt(info,"start video src");
        strcpy(url,path.toStdString().data());
        p_cap= cvCreateFileCapture(url);  //读取视频

        //    prt(info,"get %s",url.toStdString().data());
    }
    ~VideoSrc()
    {
        cvReleaseCapture(&p_cap);
        delete p_cap;
    }
    //    void set(VideoHandler &handler)
    //    {
    //        handler.frame_ori= cvQueryFrame(p_cap);
    //    }

    //    VideoHandler &operator>>(VideoHandler &handler)
    //    {

    //        int err=0;
    //        handler.frame_ori= cvQueryFrame(p_cap);
    //        if(handler.frame_ori==NULL){
    //            prt(info,"get video source fail, source url:%s",url);
    //            err=1;
    //            std::this_thread::sleep_for(chrono::milliseconds(1000));
    //        }else{
    //            //    prt(info,"get video source url:%s",url);
    //        }
    //        if(!err)
    //            handler.work(url);
    //        return handler;
    //    }
    //    VideoHandler &work(VideoHandler &handler)
    //    {

    //        int err=0;
    //        handler.frame_ori= cvQueryFrame(p_cap);

    //        if(handler.frame_ori==NULL){
    //            prt(info,"get video source fail, source url:%s",url);
    //            err=1;
    //            std::this_thread::sleep_for(chrono::milliseconds(1000));
    //        }else{
    //          prt(info,"get video source url:  size %d",handler.frame_ori->origin);
    //        }
    //        if(!err){

    //            handler.work(url);
    //        }
    //        return handler;
    //    }

    IplImage *fetch_frame()
    {
        //   prt(info,"fetching frame from %s",url);
        IplImage *ret_img;
        int err=0;
        ret_img=cvQueryFrame(p_cap);
        if(ret_img==NULL){
            //    prt(info,"get video source fail, source url:%s",url);
            err=1;
            //     std::this_thread::sleep_for(chrono::milliseconds(1000));
            //    QThread::sleep(1);
            if(video_connected_flag==true)
            {

                emit video_disconnected();
                video_connected_flag=false;
            }
            //     prt(info,"sleep done");
        }else{
            if(video_connected_flag==false)
            {

                emit video_connected();
                video_connected_flag=true;
            }
            //    prt(info,"get video source url:  size %d",ret_img->imageSize);
        }
        if(err)
            return NULL;
        else
            return ret_img;
    }
    Mat *fetch_frame_mat()
    {
        //   prt(info,"fetching frame from %s",url);
        IplImage *ret_img;
        int err=0;
        ret_img=cvQueryFrame(p_cap);
        Mat *ret_mat=new Mat(ret_img,0);
        if(ret_img==NULL){
            //    prt(info,"get video source fail, source url:%s",url);
            err=1;
            //     std::this_thread::sleep_for(chrono::milliseconds(1000));
            //    QThread::sleep(1);
            if(video_connected_flag==true)
            {

                emit video_disconnected();
                video_connected_flag=false;
            }
            //     prt(info,"sleep done");
        }else{
            if(video_connected_flag==false)
            {

                emit video_connected();
                video_connected_flag=true;
            }
            //    prt(info,"get video source url:  size %d",ret_img->imageSize);
        }
        if(err)
            return NULL;
        else
            return ret_mat;
    }
    // void operator +(int t)
    // {

    // }

    //    int  operator +(int i)
    //    {
    //       return i+1;
    //    }
    char *get_url(){
        return url;
    }
signals:
    void video_connected();
    void video_disconnected();

private:
    bool video_connected_flag;
    CvCapture *p_cap;
    char url[PATH_LEN];

};

#endif // VIDEOSRC_H
