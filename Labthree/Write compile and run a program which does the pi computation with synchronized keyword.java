import java.lang.System.*;
import java.util.concurrent.*;
public class piComputation {

	public piComputation() {
		// TODO Auto-generated constructor stub
	}
	
	static final int thCount = Runtime.getRuntime().availableProcessors();
	static int n=100000;
	static double sum = 0.0;

	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	
	//create pool
	ExecutorService executor = Executors.newFixedThreadPool(thCount);
			
			
	
	long startTime= System.currentTimeMillis();
	
	//Execute tasks
	for(int i=0; i<thCount ;i++) {
	executor.execute(new taskSum(i)); 
	}
	executor.shutdown();
	//make sure all tasks are terminated
	while(!executor.isTerminated()) {
		
	}
	long endTime = System.currentTimeMillis();
	//print
	System.out.println("PI = " + (sum * 4));
	System.out.println("Number of threads is " + thCount); 
	System.out.println("Time with " + (endTime - startTime) + " milliseconds");
	}

	


	



static class taskSum implements Runnable {
	
     int my_Rank;
	public taskSum(int my_Rank) {
		// TODO Auto-generated constructor stub
		this.my_Rank=my_Rank;
	}
	
	public void run() {
		double factor =1.0;
		int my_n= n/thCount;
		int my_first_i= my_n*my_Rank;
		int my_last_i=my_first_i + my_n;
		double my_sum=0.0;
		
		if(my_first_i %2==0) {
			factor=1.0;
		}
		else {
			factor = -1.0;
		}
		for(int i=my_first_i; i<my_last_i; i++,factor-=factor) {
			my_sum += factor /(2*i+1);
		}
	  synchronized (this){ sum += my_sum;
   	}

	}

}
}
