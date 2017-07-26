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

#ifndef _EJA_CLIENT_SHARE_WIDGET_H_
#define _EJA_CLIENT_SHARE_WIDGET_H_

#include "entity/entity_widget.h"
#include "model/client/client_share_model.h"

class QAction;
class QPoint;

namespace eja
{
	class entity;
	class entity_tree_view;

	class client_share_widget final : public entity_widget
	{
	private:
		QAction* m_add_action = nullptr;
		QAction* m_remove_action = nullptr;
		QAction* m_update_action = nullptr; 
		QAction* m_file_action = nullptr;
		QAction* m_folder_action = nullptr;

		entity_tree_view* m_tree = nullptr;
		client_share_model* m_model = nullptr;

	private:
		// Interface
		virtual void on_update() override;

		// Utility		
		bool is_file() const;
		bool is_folder() const;
		bool is_removable() const;

		// Menu
		void open_folder();
	
	private slots:
		void show_menu(const QPoint& point);

	public:
		client_share_widget(const std::shared_ptr<entity> entity, QWidget* parent = 0);
	};
}

#endif
