#include <iostream>
#include <string>

using namespace std;

class MediaFile {
protected:
    string filepath;
    double filesize;

public:
    MediaFile(string fpath, double fsize) : filepath(fpath), filesize(fsize) {}

    void play() {
        cout << "File " << filepath << " playing" << endl;
    }

    void stop() {
        cout << "File " << filepath << " stopped" << endl;
    }
};

class VisualMedia : virtual public MediaFile {
public:
    string resolution;

    VisualMedia(string path, double size, string res) : MediaFile(path, size), resolution(res) {}

    void displayResolution() {
        cout << "Resolution: " << resolution << endl;
    }
};

class AudioMedia : virtual public MediaFile {
public:
    int samplerate;

    AudioMedia(string path, double size, int rate) : MediaFile(path, size), samplerate(rate) {}

    void displaySampleRate() {
        cout << "Sample Rate is: " << samplerate << endl;
    }
};

class ImageFile : public VisualMedia {
public:
    ImageFile(string path, double size, string res) : MediaFile(path, size), VisualMedia(path, size, res) {}

    void play() {
        cout << "Displaying image: " << filepath << endl;
    }
};

class AudioFile : public AudioMedia {
public:
    AudioFile(string path, double size, int rate) : MediaFile(path, size), AudioMedia(path, size, rate) {}

    void play() {
        cout << "Playing audio: " << filepath << endl;
    }
};

class VideoFile : public VisualMedia, public AudioMedia {
public:
    VideoFile(string path, double size, string res, int rate)
        : MediaFile(path, size), VisualMedia(path, size, res), AudioMedia(path, size, rate) {}

    void play() {
        cout << "Playing video: " << filepath << endl;
        displayResolution();
        displaySampleRate();
    }
};

int main() {
    MediaFile* mediaFiles[3];

    mediaFiles[0] = new ImageFile("image.jpg", 1.5, "1920x1080");
    mediaFiles[1] = new AudioFile("audio.mp3", 3.5, 44100);
    mediaFiles[2] = new VideoFile("video.mp4", 50.0, "3840x2160", 48000);

    for (int i = 0; i < 3; i++) {
        mediaFiles[i]->play();
        mediaFiles[i]->stop();
        cout << endl;
    }

    for (int i = 0; i < 3; i++) {
        delete mediaFiles[i];
    }

    return 0;
}