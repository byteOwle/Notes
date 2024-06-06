import sys
from PyQt6.QtCore import QModelIndex, Qt, QEvent, QObject, QSortFilterProxyModel, QModelIndex, QAbstractItemModel
from PyQt6.QtGui import QStandardItemModel, QStandardItem
from PyQt6.QtWidgets import QApplication, QMainWindow, QLineEdit, QCompleter, QAbstractItemView, QComboBox, QTableView, QVBoxLayout, QListWidget, QListWidgetItem, QPushButton, QWidget, QFrame, QHBoxLayout, QListView

WINDOW_SIZE = 750

class Completer(QCompleter):
    def __init__(self) -> None:
        super().__init__()
        self.setCompletionMode(
            QCompleter.CompletionMode.PopupCompletion)
        self.setCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)
        self.setFilterMode(Qt.MatchFlag.MatchContains)

        self.closeOnLineEditClick = False
        self.event(QEvent(QEvent.Type.MouseButtonRelease))
        # self.installEventFilter(self)
        # self.widget().installEventFilter(self)
    
    # def event(self, event: QEvent) -> bool:
    #     if event.type() == QEvent.Type.MouseButtonRelease:
    #         if self.closeOnLineEditClick:
    #             self.popup().hide()
    #         else:
    #             self.popup().show()
    #     return super().event(event)
    
    def even(self, widget: QObject, event: QEvent) -> bool:
        if widget == self.widget():
            if event.type() == QEvent.Type.MouseButtonRelease:
                if self.closeOnLineEditClick:
                    self.popup().hide()
                else:
                    self.popup().show()
                    
        return super().eventFilter(widget, event)

class Window(QMainWindow):
    
    def __init__(self) -> None:
        super().__init__()
        self.setMinimumSize(WINDOW_SIZE, WINDOW_SIZE)

        centralWidget = QWidget(self)
        self.mainLayout = QVBoxLayout()

        self.topLayout = QHBoxLayout()
        self.topWidgets = QWidget()
        self.Table = QTableView()

        self.LineEdit = QLineEdit()
        self.textbox = QLineEdit()
        # self.closeOnLineEditClick = False
        
        # self.LineEdit.installEventFilter(self)
        
        self.model = self.model()

        self.completer = Completer()
        self.completer.setModel(self.model)
        # self.completer.setCompletionMode(
        #     QCompleter.CompletionMode.PopupCompletion)
        # self.completer.setCaseSensitivity(Qt.CaseSensitivity.CaseInsensitive)
        # self.completer.setFilterMode(Qt.MatchFlag.MatchContains)

        self.LineEdit.setCompleter(self.completer)

        # ------------------------------------
        # self.topLayout.addWidget(self.ComboBox, 1)
        # self.topLayout.setStretch(0, 5)
        self.topLayout.addWidget(self.LineEdit)
        self.topLayout.addWidget(self.textbox)
        self.topWidgets.setLayout(self.topLayout)

        self.mainLayout.addWidget(self.topWidgets)
        self.mainLayout.addWidget(self.Table)

        centralWidget.setLayout(self.mainLayout)
        self.setCentralWidget(centralWidget)

    # def eventFilter(self, widget: QObject, event: QEvent) -> bool:
    #     if widget == self.LineEdit:
    #         if event.type() == QEvent.Type.MouseButtonRelease:
    #             if self.closeOnLineEditClick:
    #                 self.completer.popup().hide()
    #             else:
    #                 self.completer.popup().show()
        
    #     return super().eventFilter(widget, event)
    
    
    def model(self):
        model = QStandardItemModel()
        items = ["Item 1", "Item 2", "Item 3", "Item 4", "Item 5"]
        for text in items:
            item = QStandardItem(text)
            item.setEnabled(True)
            item.setCheckable(True)
            model.appendRow(item)
        return model

    # def select_all(self):
    #     # Handle "All" button click event
    #     model = self.completer.model()
    #     for row in range(model.rowCount()):
    #         item = model.item(row)
    #         item.setCheckState(Qt.CheckState.Checked)

    # def on_apply_clicked(self):
    #     # Handle "Apply" button click event
    #     model = self.completer.model()
    #     selected_items = [model.item(row).text() for row in range(
    #         model.rowCount()) if model.item(row).checkState() == Qt.CheckState.Checked]
    #     print("Selected items:", selected_items)
    #     self.hidePopup()

    # def on_clear_clicked(self):
    #     # Handle "Clear" button click event
    #     model = self.completer.model()
    #     for row in range(model.rowCount()):
    #         model.item(row).setCheckState(Qt.CheckState.Unchecked)

    # def popup(self):
    #     # Reimplement showPopup to create a custom popup
    #     popup = QWidget()
    #     popup_layout = QVBoxLayout(popup)
    #     # popup.setWid

    #     all_item = QPushButton("All", popup)
    #     all_item.clicked.connect(self.select_all)
    #     popup_layout.addWidget(all_item)

    #     divider_top = QFrame(popup)
    #     divider_top.setFrameShape(QFrame.Shape.HLine)
    #     divider_top.setFrameShadow(QFrame.Shadow.Sunken)
    #     popup_layout.addWidget(divider_top)

    #     list_widget = QListWidget(popup)
    #     model = self.model
    #     for row in range(model.rowCount()):
    #         item = model.item(row)
    #         list_item = QListWidgetItem(item.text())
    #         list_item.setCheckState(item.checkState())
    #         list_widget.addItem(list_item)
    #     popup_layout.addWidget(list_widget)

    #     divider_bottom = QFrame(popup)
    #     divider_bottom.setFrameShape(QFrame.Shape.HLine)
    #     divider_bottom.setFrameShadow(QFrame.Shadow.Sunken)
    #     popup_layout.addWidget(divider_bottom)

    #     apply_button = QPushButton("Apply", popup)
    #     apply_button.clicked.connect(self.on_apply_clicked)
    #     clear_button = QPushButton("Clear", popup)
    #     clear_button.clicked.connect(self.on_clear_clicked)

    #     button_layout = QHBoxLayout()
    #     button_layout.addWidget(apply_button)
    #     button_layout.addWidget(clear_button)
    #     popup_layout.addLayout(button_layout)

    #     popup.setLayout(popup_layout)
    #     view = QListView()
    #     view.setLayout(popup_layout)
    #     # self.setView(view)

    #     return view


if __name__ == '__main__':
    import os
    print(os.getpid())

    app = QApplication([])
    ex = Window()
    ex.show()
    sys.exit(app.exec())
