package net.codehobby;

public class PBNum {
	private int num;//The number drawn.
	private int month, day, year;//Date the number was drawn.
	private int type;//The type of number drawn. See the PowerballTypes enum for a list of types.

	public int getNumber()
	{//Returns number.
		return num;
	}

	public void setNumber( int newNum )
	{//Set Number.
		num = newNum;
	}

}
