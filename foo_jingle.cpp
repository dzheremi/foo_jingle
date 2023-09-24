#define _WIN32_WINNT _WIN32_WINNT_WIN7
#define WINVER _WIN32_WINNT_WIN7

#include <foobar2000/SDK/foobar2000.h>
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

static constexpr const char* component_name = "FooJingle";

DECLARE_COMPONENT_VERSION(
	component_name,
	"1.0",
	"dzheremi\n\n"
	"Build: " __TIME__ ", " __DATE__
);

VALIDATE_COMPONENT_FILENAME("foo_jingle.dll");

int play_counter = 0;

class play_callback_jingle : public play_callback_static
{

public:

	virtual unsigned get_flags(void)
	{
		return(flag_on_playback_new_track);
	}

	virtual void on_playback_time(double) {}
	virtual void FB2KAPI on_playback_new_track(metadb_handle_ptr) 
	{
		play_counter++;
		if (play_counter == 3)
		{
			FB2K_console_formatter() << "Playing your jingle file...";
			mciSendString(L"open jingle.mp3 type mpegvideo alias mp3", NULL, 0, NULL);
			mciSendString(L"play mp3 from 0", NULL, 0, NULL);
			play_counter = 0;
		}
	}
	virtual void on_playback_stop(play_control::t_stop_reason) {}
	virtual void on_playback_pause(bool) {}
	virtual void on_playback_starting(play_control::t_track_command, bool) {}
	virtual void on_playback_seek(double) {}
	virtual void on_playback_edited(metadb_handle_ptr) {}
	virtual void on_playback_dynamic_info(const file_info&) {}
	virtual void on_playback_dynamic_info_track(const file_info&) {}
	virtual void on_volume_change(float) {}
};

static play_callback_static_factory_t<play_callback_jingle> g_play_callback_session;