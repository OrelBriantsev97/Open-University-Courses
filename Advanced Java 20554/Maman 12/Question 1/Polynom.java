import java.util.ArrayList;

public class Polynom {

	
	private ArrayList <PolComponent> polynom = new ArrayList<>();
	
	//constructor
	public Polynom(double[] coefficients,int[] powers)
	{
		// add exception 
		for (int i=0; i< powers.length;i++)
		{
			PolComponent pol = new PolComponent(coefficients[i],powers[i]);
			polynom.add(pol);
			
		}
		sort(polynom);
	}
	
	
	public Polynom() {}


	//returns the sum of this polynom and pol 
	public Polynom plus(Polynom pol)
	{
		Polynom sumPol = new Polynom ();
		
		int maxPower = Math.max(this.getMaxPower(),pol.getMaxPower());
		for (int power = maxPower; power >= 0; power--)
		{
			double sumCoeff = this.getCoefficient(power) + pol.getCoefficient(power);
			if(sumCoeff != 0.0)
			{
				sumPol.addMember(sumCoeff,power);
			}
				
		}
		sumPol.sort(sumPol.getPolynom());
		return sumPol;
	}
	
	//returns the diff between this polynom and pol
	public Polynom minus(Polynom pol)
	{
		Polynom diffPol = new Polynom();
		
		int maxPower = Math.max(this.getMaxPower(),pol.getMaxPower());
		
		for (int power = maxPower; power >= 0; power--)
		{
			double diffCoeff = this.getCoefficient(power) + pol.getCoefficient(power);
			if(diffCoeff != 0.0)
			{
				diffPol.addMember(diffCoeff,power);
			}	
		}
		
		diffPol.sort(diffPol.getPolynom());
		return diffPol;
	}
		
	
	//returns the derivative polynom of this polynom
	public Polynom derivative()
	{
		Polynom dePol = new Polynom();
		for(PolComponent comp : this.polynom)
		{
			double deCoeff = comp.getCoefficient() * comp.getPower();
			int dePower = comp.getPower() - 1;
			
			if(dePower >= 0 )
			{
				dePol.addMember(deCoeff, dePower);
			}
		}
		dePol.sort(dePol.getPolynom());
		return dePol;
		
	}
	
	public String toString()
	{
		StringBuilder res =  new StringBuilder();
		for(PolComponent comp : polynom)
		{
			res.append(comp).append(" ");
		}
		return res.toString();
	}
	
	public boolean equals(Object pol)
	{
		boolean equal = false;
		if(pol instanceof Polynom)
		{
			for (PolComponent thisComp : this.polynom) 
			{	
				Polynom otherPolynom = (Polynom) pol;
				for(PolComponent otherComp: otherPolynom.getPolynom())
				{
					if(thisComp.getCoefficient() == otherComp.getCoefficient() &&
							thisComp.getPower() == otherComp.getPower())
						equal = true;
					break;
				}	
				
			}
			if(!equal)
				return false; 
		}
		else 
			return false;
			
		return equal;
	}
	
	//sorting polynom according to the power of the coefficient  
	private void sort(ArrayList<PolComponent> pol)
	{
		for(int i = 0 ; i < pol.size();i++)
		{
			for(int j = i+1 ; j < pol.size()-1; j++)
			{
				if(pol.get(i).getPower() < pol.get(j).getPower())
				{
					PolComponent tempPol = pol.get(i);
					pol.set(i,pol.get(j));
					pol.set(j, tempPol);
				}
				
			}
		}
	}

	
	//returns the max power of the polynom
	private int getMaxPower()
	{
		int max = 0;
		for (PolComponent comp : polynom)
		{
		        max = Math.max(max, comp.getPower());
		}
		return max;
	}
	
	private double getCoefficient(int power)
	{
		double coefficient = 0;
		for (PolComponent comp : polynom)
		{
			if(comp.getPower() == power)
			{
				coefficient = comp.getCoefficient();
			}
				
		}
		return coefficient;
	}
	
	
	private void addMember(double coefficient, int power)
	{
		PolComponent term = new PolComponent(coefficient, power);
	    polynom.add(term);
	}
	
	private ArrayList<PolComponent> getPolynom()
	{
		return this.polynom;
	}
}
