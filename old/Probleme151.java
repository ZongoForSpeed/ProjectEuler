import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Probleme151 {
	public static void main(String[] args) {
		System.out.println(new Probleme151().run());
	}


	public String run() {
		List<Integer> startState = Arrays.asList(1);
		return String.format("%.6f", getExpectedSingles(startState) - 2);
	}


	private Map<List<Integer>,Double> expectedSingles = new HashMap<List<Integer>,Double>();

	private double getExpectedSingles(List<Integer> state) {
		if (expectedSingles.containsKey(state))
			return expectedSingles.get(state);

		double result = 0;
		if (!state.isEmpty()) {
			for (int i = 0; i < state.size(); i++) {
			List<Integer> newState = new ArrayList<Integer>(state);
			int sheet = state.get(i);
			newState.remove(i);
			for (int j = sheet + 1; j <= 5; j++)
				newState.add(j);
			Collections.sort(newState);
			result += getExpectedSingles(newState);
		}
		
		result /= state.size();
		if (state.size() == 1)
			result++;
		}
		
		expectedSingles.put(state, result);
		
		return result;
	}

}