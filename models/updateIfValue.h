
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once


template <typename T>
inline void updateIfValue(std::optional<T>& to, const std::optional<T>& from)
{
	if (from.has_value())
	{
		to = from.value();
	}
}


inline void updateIfValue(QString& to, const QString& from)
{
	if (!from.isEmpty())
	{
		to = from;
	}
}


inline void updateIfValue(QDiscordID& to, const QDiscordID& from)
{
	if (from)
	{
		to = from;
	}
}


inline void updateIfValue(QDiscordDiscriminator& to, const QDiscordDiscriminator& from)
{
	if (from)
	{
		to = from;
	}
}


inline void updateIfValue(int& to, const int& from)
{
	if (from != -1)
	{
		to = from;
	}
}


template <typename T, typename std::enable_if<std::is_scoped_enum<T>::value, int>::type* = nullptr>
inline void updateIfValue(T& to, const T& from)
{
	if (from != T::Unknown)
	{
		to = from;
	}
}


template <typename T>
inline void updateIfValue(QList<T>& to, const QList<T>& from)
{
	if (!from.isEmpty())
	{
		to = from;
	}
}


template <typename T>
inline void updateIfValue(QMap<QDiscordID, T>& to, const QMap<QDiscordID, T>& from)
{
	if (!from.isEmpty())
	{
		to = from;
	}
}


inline void updateIfValue(QDateTime& to, const QDateTime& from)
{
	if (from.isValid())
	{
		to = from;
	}
}


