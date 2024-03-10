import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.Set;

import javafx.beans.property.SimpleStringProperty;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert.AlertType;

public class PhoneBookController  {

    @FXML
    private Button addContact;
    @FXML
    private TextField addName;
    @FXML
    private TextField addPhone;
    @FXML
    private Button delContact;
    @FXML
    private TextField delName;
    @FXML
    private TextField delPhone;
    @FXML
    private TableView<Map.Entry<String, String>> table;
    @FXML
    private TableColumn<Map.Entry<String, String>, String> nameCol;
    @FXML
    private TableColumn<Map.Entry<String, String>, String> phoneCol; 
    @FXML
    private Button seaContact;
    @FXML
    private TextField seaName;
    @FXML
    private Button updContact;
    @FXML
    private TextField updName;
    @FXML
    private TextField updPhone;
    
    private PhoneBook phoneBook;
    private Alert error;
    
    @FXML
    private void initialize() {
        if (nameCol != null && phoneCol != null) {
            table.setPlaceholder(new Label("There are no contacts to view"));
            nameCol.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getKey()));
            phoneCol.setCellValueFactory(cellData -> new SimpleStringProperty(cellData.getValue().getValue()));
        } else {
            System.err.println("nameCol or phoneCol is null. Check your FXML file and controller.");
        }
    }

    //constructor
    public PhoneBookController() {
        phoneBook = new PhoneBook();
        error = new Alert(AlertType.ERROR);
        initialize();
    }

    @FXML
    void addContactPrs(ActionEvent event) {
        try {
            phoneBook.add(addName.getText(), addPhone.getText());
        } catch (InvalidPhoneNumberExc | DuplicateNameExc e) {
            error.setContentText(e.getMessage());
            error.show();
        }
        viewPhoneBook();
        addName.setText("");
        addPhone.setText("");
    }

    @FXML
    void delContactPrs(ActionEvent event) {
        try {
            phoneBook.delete(delName.getText(), delPhone.getText());
        } catch (ContactNotExistExc e) {
            error.setContentText(e.getMessage());
            error.show();
        }
        viewPhoneBook();
    }

    @FXML
    private void seaContactPrs(ActionEvent event) {
    	try
    	{
    	    table.getItems().clear();
   	        table.getItems().addAll(phoneBook.search(seaName.getText()).entrySet());
    		
    	}catch (ContactNotExistExc e)
    	{
    		error.setContentText(e.getMessage());
            error.show();
    	}
    }
    	 
    @FXML
    void updContactPrs(ActionEvent event) {
    	  try {
              phoneBook.update(updName.getText(), updPhone.getText());
          } catch (ContactNotExistExc | InvalidPhoneNumberExc e) {
              error.setContentText(e.getMessage());
              error.show();
          }
          viewPhoneBook();
          updName.setText("");
          updPhone.setText("");
      }

    private void viewPhoneBook() {
        table.getItems().clear();
        table.getItems().addAll(phoneBook.getPhoneBook().entrySet());
    }
}
