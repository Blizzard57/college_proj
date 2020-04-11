/*
 *  constructs a prototype Lane View
 *
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class LaneView implements LaneObserver, ActionListener {

	private boolean initDone;

	JFrame frame;
	Container cpanel;
	Vector<Bowler> bowlers;
	int cur=0;
	Iterator<Bowler> bowlIt;

	JPanel[][] balls;
	JLabel[][] ballLabel;
	JPanel[][] scores;
	JLabel[][] scoreLabel;
	JPanel[][] ballGrid;
	JPanel[] pins;

	JButton maintenance;
	Lane lane;

	public LaneView(Lane lane, int laneNum) {

		this.lane = lane;

		initDone = true;
		frame = new JFrame("Lane " + laneNum + ":");
		cpanel = frame.getContentPane();
		cpanel.setLayout(new BorderLayout());

		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				frame.setVisible(false);
			}
		});

		cpanel.add(new JPanel());

	}

	public void show() {
		frame.setVisible(true);
	}

	public void hide() {
		frame.setVisible(false);
	}

	private JPanel makeFrame(Party party) {

		initDone = false;
		bowlers = party.getMembers();
		int numBowlers = bowlers.size();

		JPanel panel = new JPanel();

		panel.setLayout(new GridLayout(0, 1));

		balls = new JPanel[numBowlers][23];
		ballLabel = new JLabel[numBowlers][23];
		scores = new JPanel[numBowlers][10];
		scoreLabel = new JLabel[numBowlers][10];
		ballGrid = new JPanel[numBowlers][10];
		pins = new JPanel[numBowlers];

		for (int i = 0; i != numBowlers; i++) {
			for (int j = 0; j != 23; j++) {
				ballLabel[i][j] = new JLabel(" ");
				balls[i][j] = new JPanel();
				balls[i][j].setBorder(
					BorderFactory.createLineBorder(Color.BLACK));
				balls[i][j].add(ballLabel[i][j]);
			}
		}

		for (int i = 0; i != numBowlers; i++) {
			for (int j = 0; j != 9; j++) {
				ballGrid[i][j] = new JPanel();
				ballGrid[i][j].setLayout(new GridLayout(0, 3));
				ballGrid[i][j].add(new JLabel("  "), BorderLayout.EAST);
				ballGrid[i][j].add(balls[i][2 * j], BorderLayout.EAST);
				ballGrid[i][j].add(balls[i][2 * j + 1], BorderLayout.EAST);
			}
			int j = 9;
			ballGrid[i][j] = new JPanel();
			ballGrid[i][j].setLayout(new GridLayout(0, 3));
			ballGrid[i][j].add(balls[i][2 * j]);
			ballGrid[i][j].add(balls[i][2 * j + 1]);
			ballGrid[i][j].add(balls[i][2 * j + 2]);
		}

		for (int i = 0; i != numBowlers; i++) {
			pins[i] = new JPanel();
			pins[i].setBorder(
				BorderFactory.createTitledBorder(
					((Bowler) bowlers.get(i)).getNick()));
			pins[i].setLayout(new GridLayout(0, 10));
			for (int k = 0; k != 10; k++) {
				scores[i][k] = new JPanel();
				scoreLabel[i][k] = new JLabel("  ", SwingConstants.CENTER);
				scores[i][k].setBorder(
					BorderFactory.createLineBorder(Color.BLACK));
				scores[i][k].setLayout(new GridLayout(0, 1));
				scores[i][k].add(ballGrid[i][k], BorderLayout.EAST);
				scores[i][k].add(scoreLabel[i][k], BorderLayout.SOUTH);
				pins[i].add(scores[i][k], BorderLayout.EAST);
			}
			panel.add(pins[i]);
		}

		initDone = true;
		return panel;
	}

	public void receiveLaneEvent(LaneEvent le) throws IOException {
		if (lane.isPartyAssigned()) {
			int numBowlers = le.getParty().getMembers().size();
			while (!initDone) {
				try {
					Thread.sleep(1);
				} catch (Exception e) {
					System.err.println("Error "+ e );
				}
			}

			if (le.getFrameNum() == 1
				&& le.getBall() == 0
				&& le.getIndex() == 0) {
				System.out.println("Making the frame.");
				cpanel.removeAll();
				cpanel.add(makeFrame(le.getParty()), "Center");

				JPanel buttonPanel = new JPanel();
				buttonPanel.setLayout(new FlowLayout());

				maintenance = new JButton("Maintenance Call");
				JPanel maintenancePanel = new JPanel();
				maintenancePanel.setLayout(new FlowLayout());
				maintenance.addActionListener(this);
				maintenancePanel.add(maintenance);

				buttonPanel.add(maintenancePanel);

				cpanel.add(buttonPanel, "South");

				frame.pack();

			}

			int[][] lescores = le.getCumulScore();
			for (int k = 0; k < numBowlers; k++) {
				for (int i = 0; i <= le.getFrameNum() - 1; i++) {
					if (lescores[k][i] != 0)
						scoreLabel[k][i].setText(
							(Integer.valueOf(lescores[k][i])).toString());
				}
				for (int i = 0; i < 21; i++) {
					if (((int[]) le.getScore().get(bowlers.get(k)))[i] != -1)
						if (((int[]) le.getScore().get(bowlers.get(k)))[i] == 10 && (i % 2 == 0 || i == 19)){
							ballLabel[k][i].setText("X");
						}
						else if (i > 0 && ((int[]) le.getScore().get(bowlers.get(k)))[i] + ((int[]) le.getScore().get(bowlers.get(k)))[i - 1] == 10 && i % 2 == 1){
							ballLabel[k][i].setText("/");
						}
						else if ( ((int[]) le.getScore().get(bowlers.get(k)))[i] == -2 ){
							ballLabel[k][i].setText("F");
						}
						else {
							ballLabel[k][i].setText((Integer.valueOf(((int[]) le.getScore().get(bowlers.get(k)))[i])).toString());
						}
				}
			}

			String fileContent = "";

			if (lescores[lescores.length-1][lescores[0].length - 1] != 0){
				cur++;
				if(cur==2){
					for (int i=0;i<numBowlers;i++) {
						fileContent += bowlers.get(i).getNick();
						fileContent += ",";
						fileContent += lescores[i][9];
						fileContent += ";";
					}
				}

				String saveData = "";

				try (FileReader fr = new FileReader("./data.txt")) {
					int i;
					while ((i = fr.read()) != -1)
						saveData += (char) i;
				}

				String[] arrayStr = saveData.split(";");
				String[] arrayAdd = fileContent.split(";");


				try (FileWriter fileWriter = new FileWriter("./data.txt",true)) {
					fileWriter.write(fileContent);
				}
			}
		}
	}

	public void actionPerformed(ActionEvent e) {
		if (e.getSource().equals(maintenance)) {
			lane.pauseGame();
		}
	}
}
