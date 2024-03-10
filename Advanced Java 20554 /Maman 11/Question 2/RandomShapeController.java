import java.util.Random;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.paint.Color;

public class RandomShapesController {

    @FXML
    private Button btn;

    @FXML
    private Canvas canv;
    
    private GraphicsContext gc;

    final int NUM_OF_SHAPES = 10;
    final double MAX_RECTANGLE = 0.25;
    @FXML
    public void initialize() {
    	gc = canv.getGraphicsContext2D();
    }

    @FXML
    void BtnPressed(ActionEvent event) {
    	Random random = new Random();
    	
    	double canvWidth = canv.getWidth();
    	double canvHeight = canv.getHeight();
    	
    	gc.clearRect(0, 0, canvWidth, canvHeight);
    	for (int i= 0; i <= NUM_OF_SHAPES; i++)
    	{
    		double x = random.nextDouble() * canvWidth;
    		double y = random.nextDouble() * canvHeight;
    		
    		double width = random.nextDouble() * canvWidth * MAX_RECTANGLE; // according to MAMANs requirement
    		double height = random.nextDouble() * canvHeight *MAX_RECTANGLE;
    		
    		Color randomColor  = new Color(random.nextDouble(),random.nextDouble(),random.nextDouble(),random.nextDouble());
    		gc.setFill(randomColor);
    		
    		int shapeType = random.nextInt(3);
    		//if shapeType == 0  then create rectangle
    		if(shapeType == 0 )
    		{
    			gc.fillRect(x, y, width, height);
    			
    		}
    		//if shapeType == 1  then create ellipse 
    		else if(shapeType == 1)
    		{
    			gc.fillOval(x, y, width, height);
    		}
    		//else create a line 
    		else
    		{
    			gc.setStroke(randomColor);
    			gc.strokeLine(x,y,x+ width,y+height);
    		}
        	
    		
    	}
    	
    	
    }
}
