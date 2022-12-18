package com.hisilicon.multiscreen.server.speech;

/**
 * the speech content.<br>
 *
 */
public class SpeechContent
{
    private String mContent;
    private ContentType mType;
    private ServiceType mServiceType;

    public void setContent(String content)
    {
        mContent = content;
    }

    public String getContent()
    {
        return mContent;
    }

    public void setContentType(ContentType type)
    {
        mType = type;
    }

    public ContentType getContentType()
    {
        return mType;
    }

    public ServiceType getServiceType()
    {
        return mServiceType;
    }

    public void setServiceType(ServiceType serviceType)
    {
        mServiceType = serviceType;
    }
}
