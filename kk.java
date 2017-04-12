import java.util.*;
import java.io.*;

public class kk
{
	public static void main(String[] args){
		int a[] = new int [100];
		String file = args[0];
		File inFile = new File(file);
		try(Scanner stdin = new Scanner(inFile);){
			for(int x = 0; x<100; x++){
				a[x] = Integer.parseInt(stdin.next());
			}
		}
		catch(IOException e){
				System.out.println("Error");
		}
	}

	/*private int karmarkar(MaxHeap h){

	}*/
}