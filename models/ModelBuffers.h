#ifndef MODELBUFFERS_H
#define MODELBUFFERS_H

#include <QtCore/QObject>

class Model;
class Graphics;

class PreviewBuffer;
class FaceBuffer;
class PointBuffer;

class ModelBuffers : public QObject
{
    Q_OBJECT

public:
    ModelBuffers(Model *model, Graphics *graphics, QObject *parent = nullptr);

    PreviewBuffer *previewBuffer() const { return preview; }
    FaceBuffer *faceBuffer() const { return faces; }
    PointBuffer *pointBuffer() const { return points; }

private:
    PreviewBuffer *preview;
    FaceBuffer *faces;
    PointBuffer *points;
};

#endif // MODELBUFFERS_H
