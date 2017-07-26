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

#ifndef _EJA_ENDPOINT_DELEGATE_H_
#define _EJA_ENDPOINT_DELEGATE_H_

#include <QStyledItemDelegate>

namespace eja
{
	class endpoint_delegate final : public QStyledItemDelegate
	{
		enum offset : size_t { top = 4, padding = 3, text = 22, row = 23, circle = 14 };

	private:
		size_t m_indent = 0;

	public:
		explicit endpoint_delegate(QObject* parent, const size_t indent = 0) : QStyledItemDelegate(parent), m_indent(indent) { }

		// Utility
		virtual void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
		virtual QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const override;
		void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
	};
}

#endif
