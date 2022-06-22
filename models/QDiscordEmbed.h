
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

#include "QDiscordModel.h"


class QDiscordEmbedFooter
	: public QDiscordModelBase<QDiscordEmbedFooter>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedFooter> fromJson(const QJsonObject& object);
	QDiscordEmbedFooter(const QJsonObject& object);
	QDiscordEmbedFooter() = default;
	QDiscordEmbedFooter(const QString& text, const QString& icon_url = QString(), const QString& proxy_icon_url = QString());
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QString& text() const { return _text; }
	void setText(const QString& text) { _text = text; }
	const std::optional<QString>& icon_url() const { return _icon_url; }
	void set_icon_url(const QString& icon_url) { _icon_url = icon_url; }
	const std::optional<QString>& proxy_icon_url() const { return _proxy_icon_url; }
	void set_proxy_icon_url(const QString& proxy_icon_url) { _proxy_icon_url = proxy_icon_url; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._text, "text");
		field(a, self._icon_url, "icon_url");
		field(a, self._proxy_icon_url, "proxy_icon_url");
	}

private:
	QString                _text;           // footer text
	std::optional<QString> _icon_url;       // url of footer icon (only supports http(s) and attachments)
	std::optional<QString> _proxy_icon_url; // a proxied url of footer icon
};
Q_DECLARE_METATYPE(QDiscordEmbedFooter)


class QDiscordEmbedImage
	: public QDiscordModelBase<QDiscordEmbedImage>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedImage> fromJson(const QJsonObject& object);
	QDiscordEmbedImage(const QJsonObject& object);
	QDiscordEmbedImage() = default;
	QDiscordEmbedImage(const QString& url, const QString& proxy_url = QString(), int height = 0, int width = 0);
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QString& url() const { return _url; }
	void setUrl(const QString& url) { _url = url; }
	const std::optional<QString>& proxy_url() const { return _proxy_url; }
	void set_proxy_url(const QString& proxy_url) { _proxy_url = proxy_url; }
	const std::optional<int>& height() const { return _height; }
	void set_height(const int height) { _height = height; }
	const std::optional<int>& width() const { return _width; }
	void set_width(const int width) { _width = width; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._url, "url");
		field(a, self._proxy_url, "proxy_url");
		field(a, self._height, "height");
		field(a, self._width, "width");
	}

private:
	QString                _url;       // source url of image (only supports http(s) and attachments)
	std::optional<QString> _proxy_url; // a proxied url of the image
	std::optional<int>     _height;    // height of image
	std::optional<int>     _width;     // width of image
};
Q_DECLARE_METATYPE(QDiscordEmbedImage)


class QDiscordEmbedThumbnail
	: public QDiscordModelBase<QDiscordEmbedThumbnail>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedThumbnail> fromJson(const QJsonObject& object);
	QDiscordEmbedThumbnail(const QJsonObject& object);
	QDiscordEmbedThumbnail() = default;
	QDiscordEmbedThumbnail(const QString& url, const QString& proxy_url = QString(), int height = 0, int width = 0);
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QString& url() const { return _url; }
	void setUrl(const QString& url) { _url = url; }
	const std::optional<QString>& proxy_url() const { return _proxy_url; }
	void set_proxy_url(const QString& proxy_url) { _proxy_url = proxy_url; }
	const std::optional<int>& height() const { return _height; }
	void set_height(const int height) { _height = height; }
	const std::optional<int>& width() const { return _width; }
	void set_width(const int width) { _width = width; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._url, "url");
		field(a, self._proxy_url, "proxy_url");
		field(a, self._height, "height");
		field(a, self._width, "width");
	}

private:
	QString                _url;       // source url of thumbnail (only supports http(s) and attachments)
	std::optional<QString> _proxy_url; // a proxied url of the thumbnail
	std::optional<int>     _height;    // height of thumbnail
	std::optional<int>     _width;     // width of thumbnail
};
Q_DECLARE_METATYPE(QDiscordEmbedThumbnail)


class QDiscordEmbedVideo
	: public QDiscordModelBase<QDiscordEmbedVideo>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedVideo> fromJson(const QJsonObject& object);
	QDiscordEmbedVideo(const QJsonObject& object);
	QDiscordEmbedVideo() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QString& url() const { return _url; }
	void setUrl(const QString& url) { _url = url; }
	const std::optional<QString>& proxy_url() const { return _proxy_url; }
	void set_proxy_url(const QString& proxy_url) { _proxy_url = proxy_url; }
	const std::optional<int>& height() const { return _height; }
	void set_height(const int height) { _height = height; }
	const std::optional<int>& width() const { return _width; }
	void set_width(const int width) { _width = width; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._url, "url");
		field(a, self._proxy_url, "proxy_url");
		field(a, self._height, "height");
		field(a, self._width, "width");
	}

private:
	QString                _url;       // source url of video
	std::optional<QString> _proxy_url; // a proxied url of the video
	std::optional<int>     _height;    // height of video
	std::optional<int>     _width;     // width of video
};
Q_DECLARE_METATYPE(QDiscordEmbedVideo)


class QDiscordEmbedProvider
	: public QDiscordModelBase<QDiscordEmbedProvider>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedProvider> fromJson(const QJsonObject& object);
	QDiscordEmbedProvider(const QJsonObject& object);
	QDiscordEmbedProvider() = default;
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const std::optional<QString>& name() const { return _name; }
	void set_name(const QString& name) { _name = name; }
	const std::optional<QString>& url() const { return _url; }
	void se_url(const QString& url) { _url = url; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._url, "url");
	}

private:
	std::optional<QString> _name; // name of provider
	std::optional<QString> _url;  // url of provider
};
Q_DECLARE_METATYPE(QDiscordEmbedProvider)


class QDiscordEmbedAuthor
	: public QDiscordModelBase<QDiscordEmbedAuthor>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedAuthor> fromJson(const QJsonObject& object);
	QDiscordEmbedAuthor(const QJsonObject& object);
	QDiscordEmbedAuthor() = default;
	QDiscordEmbedAuthor(const QString& name, const QString& url = QString(), const QString& icon_url = QString(), const QString& proxy_icon_url = QString());
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	const QString& name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	const std::optional<QString>& url() const { return _url; }
	void set_url(const QString& url) { _url = url; }
	const std::optional<QString>& icon_url() const { return _icon_url; }
	void set_icon_url(const QString& icon_url) { _icon_url = icon_url; }
	const std::optional<QString>& proxy_icon_url() const { return _proxy_icon_url; }
	void set_proxy_icon_url(const QString& proxy_icon_url) { _proxy_icon_url = proxy_icon_url; }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._url, "url");
		field(a, self._icon_url, "icon_url");
		field(a, self._proxy_icon_url, "proxy_icon_url");
	}

private:
	QString                _name;           // name of author
	std::optional<QString> _url;            // url of author
	std::optional<QString> _icon_url;       // url of author icon (only supports http(s) and attachments)
	std::optional<QString> _proxy_icon_url; // a proxied url of author icon
};
Q_DECLARE_METATYPE(QDiscordEmbedAuthor)


class QDiscordEmbedField
	: public QDiscordModelBase<QDiscordEmbedField>
{
	Q_GADGET
public:
	static QSharedPointer<QDiscordEmbedField> fromJson(const QJsonObject& object);
	QDiscordEmbedField(const QJsonObject& object);
	QDiscordEmbedField() = default;
	QDiscordEmbedField(const QString& name, const QString& value, std::optional<bool> inline_ = std::optional<bool>());
	void deserialize(const QJsonObject & object);
	QJsonObject serialize() const;

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._name, "name");
		field(a, self._value, "value");
		field(a, self._inline_, "inline");
	}

	const QString& name() const { return _name; }
	void setName(const QString& name) { _name = name; }
	const QString& value() const { return _value; }
	void setValue(const QString& value) { _value = value; }
	const std::optional<bool>& inline_() const { return _inline_; }
	void setInline(const bool inline_) { _inline_ = inline_; }

private:
	QString             _name; // name of field
	QString             _value; // name of field
	std::optional<bool> _inline_; // whether or not this field should display inline
};
Q_DECLARE_METATYPE(QDiscordEmbedField)


class QDiscordEmbed
	: public QDiscordModelBase<QDiscordEmbed>
{
	Q_GADGET
public:
	enum class Type : qint8
	{
		rich,    // generic embed rendered from embed attributes
		image,   // image embed
		video,   // video embed
		gifv,    // animated gif image embed rendered as a video embed
		article, // article embed
		link,    // link embed
		Unknown
	};
	Q_ENUM(Type)

	static QSharedPointer<QDiscordEmbed> fromJson(const QJsonObject& object);
	QDiscordEmbed(const QJsonObject& object);
	QDiscordEmbed() = default;
	void deserialize(const QJsonObject& object);
	QJsonObject serialize() const;

	const std::optional<QString>& title() const { return _title; }
	void setTitle(const QString& title) { _title = title; }
	const Type type() const { return _type; }
	void setType(const Type type) { _type = type; }
	const std::optional<QString>& description() const { return _description; }
	void setDescription(const QString& description) { _description = description; }
	const std::optional<QString>& url() const { return _url; }
	void setUrl(const QString& url) { _url = url; }
	const std::optional<QDateTime>& timestamp() const { return _timestamp; }
	void setTimestamp(const QDateTime& timestamp) { _timestamp = timestamp; }
	const std::optional<int>& color() const { return _color; }
	void setColor(int color) { _color = color; }
	const std::optional<QDiscordEmbedFooter>& footer() const { return _footer; }
	void setFooter(const QDiscordEmbedFooter& footer) { _footer = footer; }
	const std::optional<QDiscordEmbedImage>& image() const { return _image; }
	void setImage(const QDiscordEmbedImage& image) { _image = image; }
	const std::optional<QDiscordEmbedThumbnail>& thumbnail() const { return _thumbnail; }
	void setThumbnail(const QDiscordEmbedThumbnail& thumbnail) { _thumbnail = thumbnail; }
	const std::optional<QDiscordEmbedVideo>& video() const { return _video; }
	void setVideo(const QDiscordEmbedVideo& video) { _video = video; }
	const std::optional<QDiscordEmbedProvider>& provider() const { return _provider; }
	void setProvider(const QDiscordEmbedProvider& provider) { _provider = provider; }
	const std::optional<QDiscordEmbedAuthor>& author() const { return _author; }
	void setAuthor(const QDiscordEmbedAuthor& author) { _author = author; }
	const QList<QDiscordEmbedField>& fields() const { return _fields; }
	void addField(const QDiscordEmbedField& field) { _fields.append(field); }

	template<typename Self, class Action>
	void map(this Self&& self, Action& a) // c++23
	{
		using namespace QDiscordModel;
		field(a, self._title, "title");
		field(a, self._type, "type");
		field(a, self._description, "description");
		field(a, self._url, "url");
		field(a, self._timestamp, "timestamp");
		field(a, self._color, "color");
		field(a, self._footer, "footer");
		field(a, self._image, "image");
		field(a, self._thumbnail, "thumbnail");
		field(a, self._video, "video");
		field(a, self._provider, "provider");
		field(a, self._author, "author");
		field(a, self._fields, "fields");
	}

private:
	std::optional<QString>                _title;       // title of embed
	Type                                  _type = Type::Unknown; // type of embed (always "rich" for webhook embeds)
	std::optional<QString>                _description; // description of embed
	std::optional<QString>                _url;         // url of embed
	std::optional<QDateTime>              _timestamp;   // timestamp of embed content
	std::optional<int>                    _color;       // color code of the embed
	std::optional<QDiscordEmbedFooter>    _footer;      // footer information
	std::optional<QDiscordEmbedImage>     _image;       // image information
	std::optional<QDiscordEmbedThumbnail> _thumbnail;   // thumbnail information
	std::optional<QDiscordEmbedVideo>     _video;       // video information
	std::optional<QDiscordEmbedProvider>  _provider;    // provider information
	std::optional<QDiscordEmbedAuthor>    _author;      // author information
	QList<QDiscordEmbedField>             _fields;      // fields information
};
Q_DECLARE_METATYPE(QDiscordEmbed)


namespace QDiscordModel
{
template<>
void field(QDiscordModel::DeserializeJsonAction& action, QDiscordEmbed::Type& value, const QString& name);
template<>
void field(QDiscordModel::SerializeJsonAction& action, const QDiscordEmbed::Type& value, const QString& name);
}; // namespace QDiscordModel

