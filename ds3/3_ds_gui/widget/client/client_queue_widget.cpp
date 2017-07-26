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

#include <QAction>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QPoint>
#include <QToolBar>

#include "component/callback/callback_action.h"
#include "component/callback/callback_type.h"
#include "component/client/client_service_component.h"

#include "delegate/status_delegate.h"
#include "delegate/io/file_name_delegate.h"
#include "delegate/io/file_progress_delegate.h"
#include "entity/entity.h"
#include "entity/entity_table_view.h"
#include "font/font_awesome.h"
#include "model/client/client_queue_model.h"
#include "widget/client/client_queue_widget.h"

namespace eja
{
	// Constructor
	client_queue_widget::client_queue_widget(const entity::ptr entity, QWidget* parent /*= 0*/) : entity_widget(entity, "Queue", fa::hourglassstart, callback_type::queue, parent)
	{
		assert(thread_info::main());

		// Action
		m_remove_action = make_action("Remove", fa::minus);

		// Menu
		add_button("Remove", fa::minus, [&]() { m_model->clear(); });
		add_button("Popout", fa::clone, [&]() { popout(); });
		add_button("Close", fa::close, [&]() { close(); });

		// Layout
		auto hlayout = new QHBoxLayout;
		hlayout->setContentsMargins(0, 0, 0, 0);
		hlayout->setSpacing(0);
		hlayout->setMargin(0);

		hlayout->addWidget(m_icon);
		hlayout->addWidget(m_title);
		hlayout->addStretch(1);
		hlayout->addWidget(m_toolbar);

		m_titlebar = new QWidget(this);
		m_titlebar->installEventFilter(this);
		m_titlebar->setObjectName("menubar");
		m_titlebar->setLayout(hlayout);
		setTitleBarWidget(m_titlebar);

		// Table
		m_table = new entity_table_view(m_entity, this);
		m_model = new client_queue_model(m_entity, { "", "", "Name", "Type", "Checksum", "Size", "Threads", "Time", "Speed", "Progress" }, { 24, 24, 320, 72, 72, 72, 72, 72, 72, 104 }, this);
		init(m_table, m_model);

		// Header
		const auto hheader = m_table->horizontalHeader();
		hheader->setSectionResizeMode(client_queue_model::column::status, QHeaderView::Fixed);
		hheader->setSortIndicator(client_queue_model::column::index, Qt::SortOrder::AscendingOrder);

		// Callback
		add_callback(callback_action::add, [&](const entity::ptr entity) { m_model->add(entity); });
		add_callback(callback_action::remove, [&](const entity::ptr entity) { m_model->remove(entity); });
		add_callback(callback_action::update, [&](const entity::ptr entity) { m_model->update(); });
		add_callback(callback_action::clear, [&](const entity::ptr entity) { m_model->clear(); });

		// Delegate
		m_table->setColumnWidth(client_queue_model::column::status, 24);
		m_table->setItemDelegateForColumn(client_queue_model::column::status, new status_delegate(m_table));
		m_table->setItemDelegateForColumn(client_queue_model::column::name, new file_name_delegate(m_table));
		m_table->setItemDelegateForColumn(client_queue_model::column::progress, new file_progress_delegate(m_table));

		// Signal
		connect(m_table, &entity_table_view::customContextMenuRequested, this, &client_queue_widget::show_menu);
		connect(m_remove_action, &QAction::triggered, [&]() { m_table->remove(); });

		setWidget(m_table);
	}	

	// Menu
	void client_queue_widget::show_menu(const QPoint& pos)
	{
		assert(thread_info::main());

		const auto index = m_table->indexAt(pos);
		if (!index.isValid())
			return;

		QMenu menu(this);
		menu.addAction(m_remove_action);

		menu.exec(m_table->viewport()->mapToGlobal(pos));
	}
}
