#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include <DirectWindow.h>
#include <List.h>
#include <Looper.h>
#include <MediaDefs.h>
#include <MediaFile.h>
#include <ObjectList.h>
#include <OS.h>


struct area_desc {
	int32 offset;
	int32 height;
	int32 size;
};

enum {
	CONTROLLER_LISTEN_EVENTS = 0x1,
	CONTROLLER_LISTEN_GUI_EVENTS = 0x2,
	CONTROLLER_LISTEN_ALL = 0x3
};

extern BLooper *gControllerLooper;

class BBitmap;
class MovieEncoder;
class Controller : public BLooper {
public:

				Controller();
	virtual		~Controller();
	
	virtual void	MessageReceived(BMessage *message);

	void		ToggleCapture();
	void		TogglePause();
	
	void		EncodeMovie();
	
	void		SetUseDirectWindow(const bool &use);
	void		SetCaptureArea(const BRect &rect);
	void		SetScale(const float &scale);
	void		SetVideoDepth(const color_space &space);
	void		SetOutputFileName(const char *fileName);

	media_format_family MediaFormatFamily() const;
	media_format		MediaFormat() const;
	media_codec_info	MediaCodecInfo() const;
	
	void		SetMediaFormatFamily(const media_format_family &family);
	void		SetMediaCodec(const char* codecName);

	status_t	GetCodecsList(BObjectList<media_codec_info>& codecList) const;
	status_t	UpdateMediaFormatAndCodecsForCurrentFamily();
	
	void		UpdateDirectInfo(direct_buffer_info *info);
	void		UpdateAreaDescription(const BRect &rect);

	status_t	ReadBitmap(BBitmap *bitmap, BRect bounds);
	
private:
	thread_id			fCaptureThread;
	bool				fKillThread;
	bool				fPaused;
	
	direct_buffer_info		fDirectInfo;
	MovieEncoder*			fEncoder;
	
	char				*fTemporaryPath;

	area_desc 			fAreaDesc;
	
	BObjectList<media_codec_info>* fCodecList;
	
	void		StartCapture();
	void		EndCapture();

	void		_PauseCapture();
	void		_ResumeCapture();

	void		_EncodingFinished(const status_t status);

	void		_ForwardGUIMessage(BMessage *message);

	status_t CaptureThread();
	static int32 CaptureStarter(void *arg);
};

#endif // __CONTROLLER_H

