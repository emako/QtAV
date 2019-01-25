#include "QtAV/PreviewRenderer.h"
#include "QtAV/private/QPainterRenderer_p.h"
#include "QtAV/Filter.h"

namespace QtAV {
class PreviewRendererPrivate : public QPainterRendererPrivate
{
public:
    virtual ~PreviewRendererPrivate(){}
};

PreviewRenderer::PreviewRenderer(QObject *parent)
    : QObject(parent)
    , QPainterRenderer(*new PreviewRendererPrivate())
{
}

VideoRendererId PreviewRenderer::id() const
{
    return VideoRendererId_Dummy;
}

bool PreviewRenderer::receiveFrame(const VideoFrame &frame)
{
#if USING_FRAME
    emit updatePreview(frame);
#endif

#if USING_PIXMAP
    DPTR_D(PreviewRenderer);
    preparePixmap(frame);
    emit updatePreview(d.pixmap);
#endif

#if USING_IMAGE
    emit updatePreview(frame.toImage(QImage::Format_RGB32));
#endif

    return true;
}

bool PreviewRenderer::onSetOrientation(int value)
{
    Q_UNUSED(value);
    return true;
}

} //namespace QtAV
