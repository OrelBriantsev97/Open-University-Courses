
/**
 * MAMAN 11- class RectangleA represent a Rectangle in the Cartesian coordinate system. 
 * RectangleA have south west point, width and height.
 * @author (orel briantsev)

 */
public class RectangleB
{
    private Point _pointSW;
    private Point _pointNE;
    final int ZERO=0;
    final int ONE=1;
    final int TWO=2;
    /**
     * RectangleB constructor
     * creates a new object RectangleB by setting the south west and north east points of the rectangle.
     * if width or height are smaller then 1 or not a natural number then a default value of 1 will be initiated.
     * @param w represent the rectangle width
     * @param h represent the rectangle height
     */
    public RectangleB(int w, int h)
    {
        _pointSW=new Point(ZERO,ZERO);
        if(isValid(w) && isValid(h))
            _pointNE=new Point(w,h);    
        else if(!isValid(w) || !isValid(h))
        {
            if(isValid(w))
                _pointNE=new Point(w,1);
            else
                _pointNE=new Point(1,h);
        }
        else
            _pointNE=new Point(1,1);

    }

    /**
     * RectangleB constructor
     * creates a new object RectangleB by setting the south west and north east points of the rectangle.
     * if width or height are smaller then 1 or not a natural number then a default value of 1 will be initiated.
     * @param w represent the rectangle width
     * @param h represent the rectangle height
     * @param p represent a Point object
     */
    public RectangleB(Point p, int w, int h)
    {
        _pointSW=new Point(p);
        if(isValid(w) && isValid(h))
            _pointNE=new Point(p.getX()+w,p.getY()+h);    
        else if(!isValid(w) || !isValid(h))
        {
            if(isValid(w))
                _pointNE=new Point(p.getX()+w,ONE);
            else
                _pointNE=new Point(ONE,p.getY()+h);
        }
        else
            _pointNE=new Point(ONE,ONE);
    }

    /**
     * RectangleB constructor
     * creates a new object RectangleB by setting the south west and north east points with given values.
     * @param sw represent the rectangle width
     * @param ne represent the rectangle height
     */
    public RectangleB(Point sw, Point ne)
    {
        _pointSW=new Point(sw);//to avoid aliasing
        _pointNE=new Point(ne);

    }

    /**
     * copy constructor
     * copy the south west and north east points of a given RectangleB
     * @param r is the Rectangleb object from which we copy the south west and north east points.
     */
    public RectangleB(RectangleB r)
    {
        _pointSW=new Point(r._pointSW.getX(),r._pointSW.getY());
        _pointNE=new Point(r._pointNE.getX(),r._pointNE.getY());
    }

    //private method to check if given num is natural num and bigger then 0//
    private boolean isValid(int a)
    {
        return a>ZERO && a%ONE==ZERO;
    }

    /**
     * return the width of the RectangleB by calculating the distance between the x valve of the sw and ne points.
     * @return the width of the RectangleB.
     */
    public int getWidth() 
    {
        return Math.abs(this._pointNE.getX()-this._pointSW.getX());//absolute value of difference
    }

    /**
     *return the height of the RectangleB by calculating the distance between the y valve of the sw and ne points.
     * @return the height of the RectangleB..
     */
    public int getHeight() 
    {   
        return Math.abs(this._pointNE.getY()-this._pointSW.getY());//absolute value of difference
    }

    /**
     *return the south west point coordinates. 
     * @return the south west point coordinates.
     */
    public Point getPointSW() 
    {
        return new Point(_pointSW);
    }

    /**
     * change the width of a RectangleB.
     * @param w represent the new width.
     */
    public void setWidth(int w) 
    {
        if(isValid(w))
            _pointNE=new Point(_pointSW.getX()+w,getHeight());   
    }

    /**
     * change the width of a RectangleB by changing the north east point.
     * @param h represent the new width.
     */
    public void setHeight(int h) 
    {
        if(isValid(h))
            _pointNE=new Point(getWidth(),_pointSW.getY()+h);
    }

    /**
     * create a new north east point according to given point coordinates (creating a new point to avoid aliasing)
     * create a new south west point 
     * @param p represent the new south west point.
     */
    public void setPointSW(Point p) 
    { 
        _pointNE=new Point(getWidth()+p.getX(),getHeight()+p.getY());
        _pointSW=new Point(p);
    }

    /**
     * @return String with thw width,height and the sout west point of a RectangleB point
     * in the following format:"width=width value height=height value pointSW=point coordinates)".
     */
    public String toString() 
    {
        return "Width="+this.getWidth()+" Height="+this.getHeight()+" PointSW="+_pointSW;
    }

    /**
     * returns rectangleB perimeter
     * @return returns rectangleB perimeter.
     */
    public int getPerimeter() 
    {
        int peri=(TWO*this.getWidth())+(TWO*this.getHeight());//peri=2(a+b)
        return peri;
    }

    /**
     * returns rectangleB area.
     * @return returns rectangleB area.
     */
    public int getArea()
    {
        int area=getWidth()*getHeight();//area=a*b
        return area;
    }

    /**
     * moves the south west point to a diffrent point according the given values. 
     * @rparam deltaX represents the added x coordinate.
     * @rparam deltaY represents the added y coordinate.
     */
    public void move(int deltaX, int deltaY)
    {
        int newX=(_pointSW.getX())+deltaX;
        int newY=(_pointSW.getY())+deltaY;
        _pointSW.setX(newX);
        _pointSW.setY(newY);

    }

    /**
     * check if two given rectangles are equale by compering their width,height and south west point.
     * @return true if the two rectangles are equales.
     * @param other the rectangleB object to be compered with this rectangleB.
     */
    public boolean equals(RectangleB other) 
    {
        return this.getWidth() == other.getWidth() && this.getHeight() == other.getHeight() 
        && this._pointSW.equals(other._pointSW);

    }

    /**
     * returns the diagonal length of a rectnagleB.
     * @return  the diagonal length of a rectnagleB.
     */
    public double getDiagonalLength() 
    {
        return _pointSW.distance(getPointNE());
    }

    /**
     * check if this rectangle is larger then the given rectangle.
     * @return true if rectangle is bigger then other rectangle.
     * @param other the point object to be checked with this rectangleB.
     */
    public boolean isLarger(RectangleB other) 
    {
        return this.getPerimeter()>other.getPerimeter();
    }

    /**
     * returns the north east point of the rectangle
     * @return returns the north east point of the rectangle.
     */
    public Point getPointNE() 
    {
        _pointNE.setX(_pointSW.getX()+getWidth());
        _pointNE.setY(_pointSW.getY()+getHeight());
        return _pointNE;

    }

    /**
     * switch the height and the width value with each other by changing the north west point
     */
    public void changeSides() 
    {
        _pointNE=new Point(getHeight()+_pointSW.getX(),getWidth()+_pointSW.getY());
    }

    /**
     * check if this trangle is in the other rectangle.
     * @return true if this rectangle is in the other rectangle.
     * @param r the rectangleB object to be checked with this rectangleB.
     */
    public boolean isIn (RectangleB r) 
    {
        if(this.getPointNE().distance(r.getPointNE()) > getWidth() || this._pointSW.distance(r._pointSW) >getHeight())
            return false;
        return true;
    }

    /**
     * check if this rectangle overlaps agiven rectangle.
     * @return  if this rectangle overlaps agiven rectangle..
     * @param other the rectangleB object to be checked with this rectangleB.
     */
    public boolean overlap (RectangleB r)
    {
        if(this.getPointSW().isAbove(r.getPointNE())||this.getPointNE().isUnder(r.getPointSW())
        ||this.getPointSW().isRight(r.getPointNE())||this.getPointNE().isLeft(r.getPointSW()))
            return false;
        //checking if the the south west point is above/right to the north west
        //or the north west point is under/left to the south west 
        else 
            return true;
    }

}
