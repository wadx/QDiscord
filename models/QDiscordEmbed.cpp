
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordEmbed.h"


QSharedPointer<QDiscordEmbedFooter> QDiscordEmbedFooter::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmbedFooter> out(new QDiscordEmbedFooter());
	out->deserialize(object);
	return out;
}


QDiscordEmbedFooter::QDiscordEmbedFooter(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmbedFooter::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmbedFooter::serialize() const
{
	return serializeJson();
}


QDiscordEmbedFooter::QDiscordEmbedFooter(const QString& text, const QString& icon_url, const QString& proxy_icon_url)
{
	QDiscordEmbedAuthor();
	setText(text);
	if (!icon_url.isEmpty())
	{
		set_icon_url(icon_url);
	}
	if (!proxy_icon_url.isEmpty())
	{
		set_proxy_icon_url(proxy_icon_url);
	}
}


QSharedPointer<QDiscordEmbedImage> QDiscordEmbedImage::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmbedImage> out(new QDiscordEmbedImage());
	out->deserialize(object);
	return out;
}


QDiscordEmbedImage::QDiscordEmbedImage(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmbedImage::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmbedImage::serialize() const
{
	return serializeJson();
}


QDiscordEmbedImage::QDiscordEmbedImage(const QString& url, const QString& proxy_url, int height, int width)
{
	setUrl(url);
	if (!proxy_url.isEmpty())
	{
		set_proxy_url(proxy_url);
	}
	if (height != 0)
	{
		set_height(height);
	}
	if (width != 0)
	{
		set_width(width);
	}
}


QSharedPointer<QDiscordEmbedThumbnail> QDiscordEmbedThumbnail::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmbedThumbnail> out(new QDiscordEmbedThumbnail());
	out->deserialize(object);
	return out;
}


QDiscordEmbedThumbnail::QDiscordEmbedThumbnail(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmbedThumbnail::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmbedThumbnail::serialize() const
{
	return serializeJson();
}


QDiscordEmbedThumbnail::QDiscordEmbedThumbnail(const QString& url, const QString& proxy_url, int height, int width)
{
	setUrl(url);
	if (!proxy_url.isEmpty())
	{
		set_proxy_url(proxy_url);
	}
	if (height != 0)
	{
		set_height(height);
	}
	if (width != 0)
	{
		set_width(width);
	}
}


QSharedPointer<QDiscordEmbedVideo> QDiscordEmbedVideo::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmbedVideo> out(new QDiscordEmbedVideo());
	out->deserialize(object);
	return out;
}


QDiscordEmbedVideo::QDiscordEmbedVideo(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmbedVideo::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmbedVideo::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordEmbedProvider> QDiscordEmbedProvider::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmbedProvider> out(new QDiscordEmbedProvider());
	out->deserialize(object);
	return out;
}


QDiscordEmbedProvider::QDiscordEmbedProvider(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmbedProvider::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmbedProvider::serialize() const
{
	return serializeJson();
}


QSharedPointer<QDiscordEmbedAuthor> QDiscordEmbedAuthor::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmbedAuthor> out(new QDiscordEmbedAuthor());
	out->deserialize(object);
	return out;
}


QDiscordEmbedAuthor::QDiscordEmbedAuthor(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmbedAuthor::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmbedAuthor::serialize() const
{
	return serializeJson();
}


QDiscordEmbedAuthor::QDiscordEmbedAuthor(const QString& name, const QString& url, const QString& icon_url, const QString& proxy_icon_url)
{
	QDiscordEmbedAuthor();
	setName(name);
	if (!url.isEmpty())
	{
		set_url(url);
	}
	if (!icon_url.isEmpty())
	{
		set_icon_url(icon_url);
	}
	if (!proxy_icon_url.isEmpty())
	{
		set_proxy_icon_url(proxy_icon_url);
	}
}


QSharedPointer<QDiscordEmbedField> QDiscordEmbedField::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmbedField> out(new QDiscordEmbedField());
	out->deserialize(object);
	return out;
}


QDiscordEmbedField::QDiscordEmbedField(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmbedField::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmbedField::serialize() const
{
	return serializeJson();
}


QDiscordEmbedField::QDiscordEmbedField(const QString& name, const QString& value, std::optional<bool> inline_)
{
	QDiscordEmbedField();
	setName(name);
	setValue(value);
	if (inline_.has_value())
	{
		setInline(inline_.value());
	}
}


QSharedPointer<QDiscordEmbed> QDiscordEmbed::fromJson(const QJsonObject& object)
{
	QSharedPointer<QDiscordEmbed> out(new QDiscordEmbed());
	out->deserialize(object);
	return out;
}


QDiscordEmbed::QDiscordEmbed(const QJsonObject& object)
{
	deserialize(object);
}


void QDiscordEmbed::deserialize(const QJsonObject& object)
{
	deserializeJson(object);
}


QJsonObject QDiscordEmbed::serialize() const
{
	return serializeJson();
}


template<>
void QDiscordModel::field(QDiscordModel::DeserializeJsonAction& action, QDiscordEmbed::Type& value, const QString& name)
{
	if (action.data()[name].toString() == "rich")
	{
		value = QDiscordEmbed::Type::rich;
	}
	else if (action.data()[name].toString() == "image")
	{
		value = QDiscordEmbed::Type::image;
	}
	else if (action.data()[name].toString() == "video")
	{
		value = QDiscordEmbed::Type::video;
	}
	else if (action.data()[name].toString() == "gifv")
	{
		value = QDiscordEmbed::Type::gifv;
	}
	else if (action.data()[name].toString() == "article")
	{
		value = QDiscordEmbed::Type::article;
	}
	else if (action.data()[name].toString() == "link")
	{
		value = QDiscordEmbed::Type::link;
	}
	else
	{
		value = QDiscordEmbed::Type::Unknown;
	}
}


template<>
void QDiscordModel::field(QDiscordModel::SerializeJsonAction& action, const QDiscordEmbed::Type& value, const QString& name)
{
	switch (value)
	{
	case QDiscordEmbed::Type::rich:
		action.data().insert(name, "rich");
		break;
	case QDiscordEmbed::Type::image:
		action.data().insert(name, "image");
		break;
	case QDiscordEmbed::Type::video:
		action.data().insert(name, "video");
		break;
	case QDiscordEmbed::Type::gifv:
		action.data().insert(name, "gifv");
		break;
	case QDiscordEmbed::Type::article:
		action.data().insert(name, "article");
		break;
	case QDiscordEmbed::Type::link:
		action.data().insert(name, "link");
		break;
	}
}



