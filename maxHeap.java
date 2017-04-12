import java.util.*;
import java.io.*;

public class maxHeap
{
	public int[] array;
	public int currNum;
	public int startNum;
	public maxHeap(int startNum){
		this.startNum = startNum;
		this.array = new int[startNum];
		this.currNum = 0;
	}

	public void add(int value){
		currNum++;
		array[currNum] = value;

		bubbleUp();
	}

	private void bubbleUp(){
		int curr = this.currNum;
		while(hasParent(curr) && (parent(curr)) < array[curr]){
			swap(curr, parentIndex(curr));
			curr = parentIndex(curr);
		}
	}

	private boolean hasParent(int index){
		if index > 1
			return true;
		return false;
	}

	private int parent(int index){
		return array[parentIndex(index)];
	}
}