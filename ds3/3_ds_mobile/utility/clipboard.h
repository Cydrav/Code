//
// The MIT License(MIT)
//
// Copyright(c) 2014 Demonsaw LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef _EJA_CLIPBOARD_H_
#define _EJA_CLIPBOARD_H_

#include <QObject>
#include <QString>

namespace eja
{
	class clipboard : public QObject
	{
		Q_OBJECT

		Q_PROPERTY(QString text READ get_text WRITE set_text NOTIFY textChanged)
		Q_PROPERTY(bool exists READ exists CONSTANT)

	private:
		QString m_text;

	public:
		explicit clipboard(QObject* parent = nullptr) : QObject(parent) { }

		// Has
		bool exists() const;

		// Set
		void set_text(const QString& text);

		// Get
		QString get_text() const;

	signals:
		void textChanged();
	};
}

#endif
