
public class PolComponent {
	
	private double coefficient;
	private int power;
	
	public PolComponent(double coef , int power)
	{
		this.coefficient = coef;
		this.power = power;
		
	}

	public int getPower()
	{
		return this.power;
	}
	
	public double getCoefficient()
	{
		return this.coefficient;
	}
	
	public String toString()
	{
		String str = "";
		if(this.coefficient > 0)
			str = str + this.coefficient + "x";
		if(this.coefficient < 0)
			str = str + '+' + this.coefficient + "x";
		if(this.power > 1)
			str=str + "^" + this.power;
		return str;
	}
	
	
}
