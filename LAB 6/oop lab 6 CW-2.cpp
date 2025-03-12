#include <iostream>
#include <string>

using namespace std;

class MediaFile {
protected:
    string filepath;
    double filesize;

public:
    MediaFile() {}  

    MediaFile(string fpath, double fsize) : filepath(fpath), filesize(fsize) {}

    void play() {
        cout << "Media File " << filepath << " playing" << endl;
    }

    void stop() {
        cout << "Media File " << filepath << " stopped" << endl;
    }
};

class VisualMedia : virtual public MediaFile {
public:
    string resolution;

    VisualMedia(string res) : resolution(res) {}

    void displayResolution() {
        cout << "Resolution: " << resolution << endl;
    }
};


class AudioMedia : virtual public MediaFile {
public:
    int samplerate;

    AudioMedia(int rate) : samplerate(rate) {}

    void displaySampleRate() {
        cout << "Sample Rate: " << samplerate << " Hz" << endl;
    }
};

class ImageFile : public VisualMedia {
public:
    ImageFile(string path, double size, string res)
        : MediaFile(path, size), VisualMedia(res) {}

    void play() {
        cout << "Displaying image: " << filepath << endl;
    }

    void stop() {
        cout << "Stopped displaying image: " << filepath << endl;
    }
};

class AudioFile : public AudioMedia {
public:
    AudioFile(string path, double size, int rate)
        : MediaFile(path, size), AudioMedia(rate) {}

    void play() {
        cout << "Playing audio: " << filepath << endl;
    }

    void stop() {
        cout << "Stopped audio: " << filepath << endl;
    }
};

class VideoFile : public VisualMedia, public AudioMedia {
public:
    VideoFile(string path, double size, string res, int rate)
        : MediaFile(path, size), VisualMedia(res), AudioMedia(rate) {}

    void play() {
        cout << "Playing video: " << filepath << endl;
        displayResolution();
        displaySampleRate();
    }

    void stop() {
        cout << "Stopped video: " << filepath << endl;
    }
};

int main() {
    ImageFile image("image.jpg", 1.5, "1920x1080");
    AudioFile audio("audio.mp3", 3.5, 44100);
    VideoFile video("video.mp4", 50.0, "3840x2160", 48000);

    cout << "\n--- Image File ---" << endl;
    image.play();
    image.stop();

    cout << "\n--- Audio File ---" << endl;
    audio.play();
    audio.stop();

    cout << "\n--- Video File ---" << endl;
    video.play();
    video.stop();

    return 0;
}
