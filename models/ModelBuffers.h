#ifndef MODELBUFFERS_H
#define MODELBUFFERS_H

#include <QtCore/QObject>

class Model;
class Graphics;

class PreviewBuffer;

class ModelBuffers : public QObject
{
    Q_OBJECT

public:
    ModelBuffers(Model *model, Graphics *graphics, QObject *parent = nullptr);

    PreviewBuffer *previewBuffer() const { return preview; }

private:
    PreviewBuffer *preview;
};

#endif // MODELBUFFERS_H
