
/**
 * MAMAN 11- class RectangleA represent a Rectangle in the Cartesian coordinate system. 
 * RectangleA have south west point, width and height.
 * @author (orel briantsev)

 */
public class RectangleA
{
    final int ZERO=0;
    final int ONE=1;
    final int TWO=2;
    private int _width;
    private int _height;
    private Point _pointSW;
    /**
     * RectangleA constructor
     * creates a new object RectangleA
     * if width or Height are smaller then 1 or not a natural number then a default value of 1 will be initiated.
     * @param w represent the rectangle width
     * @param h represent the rectangle height
     */
    public RectangleA(int w, int h)
    {
        _pointSW=new Point(ZERO,ZERO);
        if(isValid(w))
            _width=w;
        else
            _width=ONE;
        if(isValid(h))
            _height=h;
        else
            _height=ONE;
    }

    /**
     * RectangleA constructor
     * creates a new object RectangleA
     * @param w represent the rectangle width
     * @param h represent the rectangle height
     * @param p represent a point object
     */
    public RectangleA(Point p, int w, int h) 
    {
        _pointSW=new Point(p);
        if(isValid(w))
            _width=w;
        else
            _width=ONE;
        if(isValid(h))
            _height=h;
        else
            _height=ONE;
    }

    /**
     * RectangleA constructor
     * creates a new object RectangleA and calculatind width and height according to the sw and ne points
     * @param sw represent the south west point 
     * @param ne represent the north east point
     */
    public RectangleA(Point sw, Point ne)
    {
        _width=Math.abs(ne.getX()-sw.getX());//absolute value of the difference
        _height=Math.abs(ne.getY()-sw.getY());//absolute value of the difference
        _pointSW=new Point(sw);

    }

    /**
     * copy constructor
     * copy the width,height and south westm point
     * @param r is the RectangleA object from which we copy width,height and south west point from.
     */
    public RectangleA(RectangleA r)
    {
        _width=r._width;
        _height=r._height;
        _pointSW=r._pointSW;
    }

    //private method to check if given num is natural num and bigger then 0//
    private boolean isValid(int a)
    {
        return a>ZERO && a%ONE==ZERO;
    }

    /**
     * return the width of the RectangleA.
     * @return the width of the RectangleA..
     */
    public int getWidth() 
    {
        return _width;
    }

    /**
     * return the height of the RectangleA.
     * @return the height of the RectangleA..
     */
    public int getHeight() 
    {
        return _height;
    }

    /**
     * return a new point with the south west coordinates.
     * @return a new point with the south west coordinates
     */
    public Point getPointSW() 
    {
        return new Point(_pointSW);
    }

    /**
     * change the width of a RectangleA.
     * @param w represent the new width.
     */
    public void setWidth(int w) 
    {
        if(isValid(w))
            _width=w;
    }

    /**
     * change the height of a RectangleA.
     * @param h represent the new height.
     */
    public void setHeight(int h) 
    {
        if(isValid(h))
            _height=h;
    }

    /**
     * change the south west point coordinates (creating a new point to avoid aliasing)
     * @param p represent the new south west point.
     */
    public void setPointSW(Point p) 
    {   _pointSW=new Point(p);// to avoid aliasing
    }

    /**
     * @return String with thw width,height and the sout west point of a RectangleA point
     * in the following format:"width=width value height=height value pointSW=point coordinates)".
     */
    public String toString() 
    {
        return "Width="+_width+" Height="+_height+" PointSW="+_pointSW;
    }

    /**
     * returns rectangleA perimeter
     * @return returns rectangleA perimeter.
     */
    public int getPerimeter() 
    {
        int peri=(TWO*_width)+(TWO*_height);//peri=2(a+b)
        return peri;
    }

    /**
     * returns rectangleA area.
     * @return returns rectangleA area.
     */
    public int getArea()
    {
        int area=_width*_height;//area=a*b
        return area;
    }

    /**
     * moves the south west point to a diffrent point according the given values. 
     * @rparam deltaX represents the added x coordinate.
     * @rparam deltaY represents the added y coordinate.
     */
    public void move(int deltaX, int deltaY)
    {
        int newX=(_pointSW.getX())+deltaX;//newX=x value+deltaX
        int newY=(_pointSW.getY())+deltaY;//newY=y value+deltaY
        _pointSW=new Point (newX,newY);

    }

    /**
     * check if two given rectangles are equale by compering their width,height and south west point.
     * @return true if the two rectangles are equales.
     * @param other the rectangleA object to be compered with this rectangleA.
     */
    public boolean equals(RectangleA other) 
    {
        if(this._width == other._width && this._height == other._height && this._pointSW.equals(other._pointSW))
            return true;
        else
            return false;
    }

    /**
     * returns the diagonal lengthof a rectnagleA.
     * @return  the diagonal lengthof a rectnagleA.
     */
    public double getDiagonalLength() 
    {
        return _pointSW.distance(getPointNE());
    }

    /**
     * check if this rectangle is larger then the given rectangle.
     * @return true if rectangle is bigger then other rectangle.
     * @param other the point object to be checked with this rectangleA.
     */
    public boolean isLarger(RectangleA other) 
    {
        return this.getPerimeter()>other.getPerimeter();
    }

    /**
     * returns the north east point of the rectangle
     * @return returns the north east point of the rectangle.
     */
    public Point getPointNE() 
    {
        return new Point(_pointSW.getX()+_width,_pointSW.getY()+_height);//to avoid aliasing
    }

    /**
     * switch the height and the width value with each other.
     */
    public void changeSides() 
    {
        int newWidth=_height;//newWidth used as temp value
        _height=_width;
        _width=newWidth;
    }

    /**
     * check if this trangle is in the other rectangle.
     * @return true if this rectangle is in the other rectangle.
     * @param r the rectangleA object to be checked with this rectangleA.
     */
    public boolean isIn (RectangleA r) 
    {
        if(this.getPointNE().distance(r.getPointNE()) > _width || this._pointSW.distance(r._pointSW) >_height)
            return false;
        return true;
    }

    /**
     * check if this rectangle overlaps agiven rectangle.
     * @return  if this rectangle overlaps agiven rectangle..
     * @param other the rectangleA object to be checked with this rectangleA.
     */
    public boolean overlap (RectangleA r)
    {
        if(this._pointSW.isAbove(r.getPointNE())||this.getPointNE().isUnder(r._pointSW)
        ||this._pointSW.isRight(r.getPointNE())||this.getPointNE().isLeft(r._pointSW))
            return false;
        //checking if the the south west point is above/right to the north west
        //or the north west point is under/left to the south west 
        else 
            return true;
    }
}
