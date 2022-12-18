package com.hisilicon.android.errorreport;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Properties;

import javax.activation.CommandMap;
import javax.activation.DataHandler;
import javax.activation.FileDataSource;
import javax.activation.MailcapCommandMap;
import javax.mail.Authenticator;
import javax.mail.PasswordAuthentication;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.mail.internet.MimeUtility;

import android.util.Log;

import com.hisilicon.android.errorreport.MailPropertiesUtil;

public class SendEmailClient {

	private String username = "";
	private String pwd = "";
	private String from = ""; // 发件人
	private String to = ""; // 收件人
	private String mail_protocol = "";
	private String mail_auth = "";
	private String mail_host = "";
	private String mail_port = "";
	private String protocol = "";
	private String auth = "";
	private String host = "";
	private String port = "";
	private String content ="";//发送内容
	private String subject ="";//主题

	public SendEmailClient() {
		super();
		Properties prop = MailPropertiesUtil.loadProperties();
		username = prop.get("username").toString();
		pwd =prop.get("pwd").toString();
		from =prop.get("from").toString();
		to=prop.get("to").toString();
		mail_protocol=prop.get("mail_protocol").toString();
		mail_auth=prop.get("mail_auth").toString();
		mail_host=prop.get("mail_host").toString();
		mail_port=prop.get("mail_port").toString();
		protocol=prop.get("protocol").toString();
		auth=prop.get("auth").toString();
		host=prop.get("host").toString();
		port=prop.get("port").toString();
		content=prop.get("content").toString();
		subject=prop.get("subject").toString();
		Log.d("tangxiaodi","SendEmailClient [username=" + username + ", pwd=" + pwd
				+ ", from=" + from + ", to=" + to + ", mail_protocol="
				+ mail_protocol + ", mail_auth=" + mail_auth + ", mail_host="
				+ mail_host + ", mail_port=" + mail_port + ", protocol="
				+ protocol + ", auth=" + auth + ", host=" + host + ", port="
				+ port + ", content=" + content + ", subject=" + subject
				+ ", getClass()=" + getClass() + ", hashCode()=" + hashCode()
				);
	}

	public boolean sendEmailWithPart(String path,String mContent) {
		Properties props = new Properties();
		props.put(mail_protocol, protocol);
		props.put(mail_host, host);//
		props.put(mail_port, port); //
		props.put(mail_auth, auth);//
		Session session = Session.getInstance(props, new Authenticator() {
			@Override
			protected PasswordAuthentication getPasswordAuthentication() {
				// TODO Auto-generated method stub
				return new PasswordAuthentication(username, pwd);
			}
		});
		// 增加这一段是要增加对附件的支持.
		MailcapCommandMap mc = (MailcapCommandMap) CommandMap
				.getDefaultCommandMap();
		mc.addMailcap("text/html;; x-java-content-handler=com.sun.mail.handlers.text_html");
		mc.addMailcap("text/xml;; x-java-content-handler=com.sun.mail.handlers.text_xml");
		mc.addMailcap("text/plain;; x-java-content-handler=com.sun.mail.handlers.text_plain");
		mc.addMailcap("multipart/*;; x-java-content-handler=com.sun.mail.handlers.multipart_mixed");
		mc.addMailcap("message/rfc822;; x-java-content-handler=com.sun.mail.handlers.message_rfc822");
		CommandMap.setDefaultCommandMap(mc);

		try {
			//发送到一个或多个人
			List<InternetAddress> list = new ArrayList<InternetAddress>();
			String[] strArray = to.split(";");
			for (int i = 0; i < strArray.length; i++) {
				list.add(new InternetAddress(strArray[i]));
			}
			InternetAddress[] toAddress = (InternetAddress[]) list .toArray(new InternetAddress[list.size()]);
			InternetAddress fromAddress = new InternetAddress(from);

			// 内容
			MimeBodyPart mimeBodyText = new MimeBodyPart();
                    if(mContent != null && mContent.equals(""))
			    mimeBodyText.setContent(content, "text/plain;charset=gbk");
                    else
                        mimeBodyText.setContent(mContent, "text/plain;charset=gbk");
			// 附件
			MimeBodyPart mimeBodyPart = new MimeBodyPart();
			FileDataSource fds = new FileDataSource(path);
			mimeBodyPart.setDataHandler(new DataHandler(fds));
			mimeBodyPart.setFileName(MimeUtility.encodeText(fds.getName(), "utf-8", "B"));// 解决文件名乱码

			MimeMultipart allMultipart = new MimeMultipart("mixed");
			// 加入内容,附件
			allMultipart.addBodyPart(mimeBodyText);
			allMultipart.addBodyPart(mimeBodyPart);

			MimeMessage message = new MimeMessage(session);
			message.setFrom(fromAddress);
			message.setSubject(subject);
			message.setSentDate(new Date());
			message.setContent(allMultipart);
			message.addRecipients(javax.mail.Message.RecipientType.TO, toAddress);
			message.saveChanges();

			Transport transport = session.getTransport(protocol);
			transport.connect(host, username, pwd);
			Transport.send(message);
			transport.close();

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}
		return true;
	}

}
