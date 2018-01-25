/**
 * ��򵥵Ļ���FFmpeg��������-��׿
 * Simplest FFmpeg Android Streamer
 *
 * ������ Lei Xiaohua
 * leixiaohua1020@126.com
 * �й���ý��ѧ/���ֵ��Ӽ���
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 * �������ǰ�׿ƽ̨����򵥵Ļ���FFmpeg����ý����������
 * �����Խ���Ƶ��������ý�����ʽ���ͳ�ȥ��
 *
 * This software is the simplest streamer based on FFmpeg in Android.
 * It can stream local media file to streaming media server (in RTMP).
 */


#include <stdio.h>
#include <time.h> 

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/log.h"

#ifdef ANDROID
#include <jni.h>
#include <android/log.h>
#define LOGE(format, ...)  __android_log_print(ANDROID_LOG_ERROR, "error", format, ##__VA_ARGS__)
#define LOGI(format, ...)  __android_log_print(ANDROID_LOG_INFO,  "info", format, ##__VA_ARGS__)
#else
#define LOGE(format, ...)  printf("(>_<) " format "\n", ##__VA_ARGS__)
#define LOGI(format, ...)  printf("(^_^) " format "\n", ##__VA_ARGS__)
#endif


//Output FFmpeg's av_log()
void custom_log(void *ptr, int level, const char* fmt, va_list vl){

	//To TXT file
	FILE *fp=fopen("/storage/emulated/0/av_log.txt","a+");
	if(fp){
		vfprintf(fp,fmt,vl);
		fflush(fp);
		fclose(fp);
	}

	//To Logcat
	//LOGE(fmt, vl);
}

/**
  ffmpeg 推流
**/
JNIEXPORT jint JNICALL Java_com_leixiaohua1020_sffmpegandroidstreamer_MainActivity_stream
  (JNIEnv *env, jobject obj, jstring input_jstr, jstring output_jstr)
{
    /**
    AVOutputFormat 结构主要包含的信息有：封装名称描述，编码格式信息(video/audio 默认编码格式，支持的编码格式列表)，
    一些对封装的操作函数(write_header,write_packet,write_tailer等)
    **/
    AVOutputFormat *ofmt = NULL;
    /**
    在使用FFMPEG进行开发的时候，AVFormatContext是一个贯穿始终的数据结构，很多函数都要用到它作为参数。
    它是FFMPEG解封装（flv，mp4，rmvb，avi）功能的结构体。
    */
	AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
	AVPacket pkt;

	int ret, i;
	char input_str[500]={0};
	char output_str[500]={0};
	char info[1000]={0};
	sprintf(input_str,"%s",(*env)->GetStringUTFChars(env,input_jstr, NULL));
	sprintf(output_str,"%s",(*env)->GetStringUTFChars(env,output_jstr, NULL));

	//input_str  = "cuc_ieschool.flv";
	//output_str = "rtmp://localhost/publishlive/livestream";
	//output_str = "rtp://233.233.233.233:6666";

	//FFmpeg av_log() callback
	av_log_set_callback(custom_log);

	av_register_all();
	//Network
    /**
    使用ffmpeg类库进行开发的时候，打开流媒体（或本地文件）的函数是avformat_open_input()。
    其中打开网络流的话，前面要加上函数avformat_network_init()。
    **/
	avformat_network_init();

	//Input  ，打开流媒体 ,将一些参数赋值给ifmt类似回调
	if ((ret = avformat_open_input(&ifmt_ctx, input_str, 0, 0)) < 0) {
		LOGE( "Could not open input file.");
		goto end;
	}
	// 该函数可以读取一部分视音频数据并且获得一些相关的信息,再赋值给ifmt_ctx, 上面open后信息获取还是不全的，所以还需要单独find
	if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
		LOGE( "Failed to retrieve input stream information");
		goto end;
	}

	int videoindex=-1;
	//找到视频流
	for(i=0; i<ifmt_ctx->nb_streams; i++) 
		if(ifmt_ctx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
			videoindex=i;
			break;
		}
	//Output avformat_alloc_output_context2()函数可以初始化一个用于输出的AVFormatContext结构体
	avformat_alloc_output_context2(&ofmt_ctx, NULL, "flv",output_str); //RTMP
	//avformat_alloc_output_context2(&ofmt_ctx, NULL, "mpegts", output_str);//UDP

	if (!ofmt_ctx) {
		LOGE( "Could not create output context\n");
		ret = AVERROR_UNKNOWN;
		goto end;
	}
	ofmt = ofmt_ctx->oformat;
	for (i = 0; i < ifmt_ctx->nb_streams; i++) {
		//Create output AVStream according to input AVStream
		AVStream *in_stream = ifmt_ctx->streams[i];
		AVStream *out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
		if (!out_stream) {
			LOGE( "Failed allocating output stream\n");
			ret = AVERROR_UNKNOWN;
			goto end;
		}
		//Copy the settings of AVCodecContext
		ret = avcodec_copy_context(out_stream->codec, in_stream->codec);
		if (ret < 0) {
			LOGE( "Failed to copy context from input to output stream codec context\n");
			goto end;
		}
		out_stream->codec->codec_tag = 0;
		if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
			out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
	}

	//Open output URL
	if (!(ofmt->flags & AVFMT_NOFILE)) {
		ret = avio_open(&ofmt_ctx->pb, output_str, AVIO_FLAG_WRITE);
		if (ret < 0) {
			LOGE( "Could not open output URL '%s'", output_str);
			goto end;
		}
	}
	//Write file header
	ret = avformat_write_header(ofmt_ctx, NULL);
	if (ret < 0) {
		LOGE( "Error occurred when opening output URL\n");
		goto end;
	}

	int frame_index=0;

	int64_t start_time=av_gettime();
	while (1) {
		AVStream *in_stream, *out_stream;
		//Get an AVPacket
		ret = av_read_frame(ifmt_ctx, &pkt);
		if (ret < 0)
			break;
		//FIX��No PTS (Example: Raw H.264)
		//Simple Write PTS
		if(pkt.pts==AV_NOPTS_VALUE){
			//Write PTS
			AVRational time_base1=ifmt_ctx->streams[videoindex]->time_base;
			//Duration between 2 frames (us)
			int64_t calc_duration=(double)AV_TIME_BASE/av_q2d(ifmt_ctx->streams[videoindex]->r_frame_rate);
			//Parameters
			pkt.pts=(double)(frame_index*calc_duration)/(double)(av_q2d(time_base1)*AV_TIME_BASE);
			pkt.dts=pkt.pts;
			pkt.duration=(double)calc_duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);
		}
		//Important:Delay
		if(pkt.stream_index==videoindex){
			AVRational time_base=ifmt_ctx->streams[videoindex]->time_base;
			AVRational time_base_q={1,AV_TIME_BASE};
			int64_t pts_time = av_rescale_q(pkt.dts, time_base, time_base_q);
			int64_t now_time = av_gettime() - start_time;
			if (pts_time > now_time)
				av_usleep(pts_time - now_time);

		}

		in_stream  = ifmt_ctx->streams[pkt.stream_index];
		out_stream = ofmt_ctx->streams[pkt.stream_index];
		/* copy packet */
		//Convert PTS/DTS
		pkt.pts = av_rescale_q_rnd(pkt.pts, in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX);
		pkt.dts = av_rescale_q_rnd(pkt.dts, in_stream->time_base, out_stream->time_base, AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX);
		pkt.duration = av_rescale_q(pkt.duration, in_stream->time_base, out_stream->time_base);
		pkt.pos = -1;
		//Print to Screen
		if(pkt.stream_index==videoindex){
			LOGE("Send %8d video frames to output URL\n",frame_index);
			frame_index++;
		}
		//ret = av_write_frame(ofmt_ctx, &pkt);
		ret = av_interleaved_write_frame(ofmt_ctx, &pkt);

		if (ret < 0) {
			LOGE( "Error muxing packet\n");
			break;
		}
		av_free_packet(&pkt);
		
	}
	//Write file trailer
	av_write_trailer(ofmt_ctx);
end:
	avformat_close_input(&ifmt_ctx);
	/* close output */
	if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
		avio_close(ofmt_ctx->pb);
	avformat_free_context(ofmt_ctx);
	if (ret < 0 && ret != AVERROR_EOF) {
		LOGE( "Error occurred.\n");
		return -1;
	}
	return 0;
}

