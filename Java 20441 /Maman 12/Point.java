
/**
 * MAMAN 11- class Point represent a point in the Cartesian coordinate system. 
 * @author (orel briantsev)

 */
public class Point
{
    private int _x;
    private int _y;

    /**
     * point constructor
     * creates a new object point
     * @param x represent the x coordinate
     * @param y represent the y coordinate
     */
    public Point(int x ,int y)
    {
        _x=x;
        _y=y;
    }

    /**
     * copy constructor for Point.
     * Construct a point with the same coordinates as the other.
     * @param other the point object from which to construct new one.
     */
    public Point(Point other)
    {
        _x=other.getX();
        _y=other.getY();
    }

    /**
     * returns the X coordinate of Point.
     * @return the X coordinate of Point.
     */
    public int getX()
    {
        return this._x;
    }

    /**
     * returns the Y coordinate of Point.
     * @return the Y coordinate of Point.
     */
    public int getY()
    {
        return this._y;
    }

    /**
     * change the x coordinate of Point.
     * @param num the new x coordinate of Point.
     */
    public void setX (int num)
    {
        _x=num;
    }

    /**
     * change the y coordinate of Point.
     * @param num the new y coordinate of Point.
     */
    public void setY (int num)
    {
        _y=num;
    }

    /**
     * @return String that represents this point
     * in the following format:"(x value,y value)".
     */
    public String toString()
    {
        return "("+_x+","+_y+")";
    }

    /**
     * check if two point have the same x any coordinates.
     * @return true if two point have the same x any coordinates.
     * @param other the point object to be compered with this Point.
     */
    public boolean equals (Point other)
    {
        return this.getX() == other.getX() && this.getY() == other.getY();
    }

    /**
     * check if this point is above other point by checking the y coordinates value.
     * @return true if this point is above other point.
     * @param other the point object to be checked with this Point.
     */
    public boolean isAbove (Point other)
    {
        return this.getY()>other.getY();
    }

    /**
     * check if this point is under other point by using "isAbove" method.
     * @return true if this point is under other point.
     * @param other the point object to be checked with this Point.
     */
    public boolean isUnder (Point other)
    {
        return !this.isAbove(other);//if this point is not above other point then this point is under other point
    }

    /**
     * check if this point is left other point by checking the x coordinates value.
     * @return true if this point is left to the other point.
     * @param other the point object to be checked with this Point.
     */
    public boolean isLeft (Point other)
    {
        return this.getX() < other.getX();

    }

    /**
     * check if this point is right other point by using the "isLeft" method.
     * @return true if this point is right to other point.
     * @param other the point object to be checked with this Point.
     */
    public boolean isRight (Point other)
    {
        return !this.isLeft(other);//if this point is not left to other point then this point is right to other point
    }

    /**
     * moves the point to a diffrent spot acoording to given values.
     * @param deltaX represent the x corrdinate added value.
     * @param deltay represent the y corrdinate added value..
     */
    public void move (int deltaX, int deltaY)
    {
        _x+=deltaX;
        _y+=deltaY;
    }

    /**
     * returns the distance between 2 givin point.
     * @return the distance between 2 givin point.
     * @param p the point object which we check the distance from.
     */
    public double distance (Point p)
    {
        double xDistance=Math.pow((this.getX()-p.getX()),2);//pythagoras
        double yDistance=Math.pow((this.getY()-p.getY()),2);
        double distance=Math.sqrt(xDistance+yDistance);
        return distance;
    }

}
