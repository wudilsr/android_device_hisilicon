package com.hisilicon.android.errorreport;

import java.io.IOException;
import java.util.Properties;

public class MailPropertiesUtil {

    private static String propFile;

    static {
        propFile = "/assets/mail.properties";

    }
    public static Properties loadProperties(){

        Properties properties = new Properties();
        try {
            properties.load(MailPropertiesUtil.class.getResourceAsStream(propFile));
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return properties;
    }

}
