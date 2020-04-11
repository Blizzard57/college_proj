/** To change this generated comment edit the template variable "typecomment":
  * Window>Preferences>Java>Templates.
  * To enable and disable the creation of type comments go to
  * Window>Preferences>Java>Code Generation.*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class LaneStatusView implements ActionListener, LaneObserver, PinsetterObserver {

	private JPanel jp;

	private JLabel curBowler;
	private JLabel pinsDown;
	private JButton viewLane;
	private JButton maintenance;
	private JButton viewPinSetter;
	private JButton play;
	private JButton query;

	private PinSetterView psv;
	private LaneView lv;
	private Lane lane;
	int laneNum;

	boolean laneShowing;
	boolean psShowing;
	boolean isPlay = true;
	boolean isMaintained = false;

	public LaneStatusView(Lane lane, int laneNum) {

		this.lane = lane;
		this.laneNum = laneNum;

		laneShowing=false;
		psShowing=false;

		psv = new PinSetterView( laneNum );
		Pinsetter ps = lane.getPinsetter();
		ps.subscribe(psv);

		lv = new LaneView( lane, laneNum );
		lane.subscribe(lv);


		jp = new JPanel();
		jp.setLayout(new FlowLayout());
		JLabel cLabel = new JLabel( "Now Bowling: " );
		curBowler = new JLabel( "(no one)" );
		JLabel fLabel = new JLabel( "Foul: " );
		JLabel foul = new JLabel(" ");
		JLabel pdLabel = new JLabel( "Pins Down: " );
		pinsDown = new JLabel( "0" );

		// Button Panel
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new FlowLayout());

		viewLane = new JButton("View Lane");
		JPanel viewLanePanel = new JPanel();
		viewLanePanel.setLayout(new FlowLayout());
		viewLane.addActionListener(this);
		viewLanePanel.add(viewLane);

		viewPinSetter = new JButton("Pinsetter");
		JPanel viewPinSetterPanel = new JPanel();
		viewPinSetterPanel.setLayout(new FlowLayout());
		viewPinSetter.addActionListener(this);
		viewPinSetterPanel.add(viewPinSetter);

		maintenance = new JButton("     ");
		maintenance.setBackground( Color.GREEN );
		JPanel maintenancePanel = new JPanel();
		maintenancePanel.setLayout(new FlowLayout());
		maintenance.addActionListener(this);
		maintenancePanel.add(maintenance);

		play = new JButton("Play/Pause");
		play.setBackground( Color.GREEN );
		JPanel playPanel = new JPanel();
		playPanel.setLayout(new FlowLayout());
		play.addActionListener(this);
		playPanel.add(play);

		viewLane.setEnabled( false );
		viewPinSetter.setEnabled( false );


		buttonPanel.add(viewLanePanel);
		buttonPanel.add(viewPinSetterPanel);
		buttonPanel.add(maintenancePanel);
		buttonPanel.add(playPanel);

		jp.add( cLabel );
		jp.add( curBowler );
		jp.add( fLabel );
		jp.add(foul);
		jp.add( pdLabel );
		jp.add( pinsDown );
		jp.add(buttonPanel);

	}

	public JPanel showLane() {
		return jp;
	}

	public void ifLaneAssigned(ActionEvent e){
		if (e.getSource().equals(viewPinSetter)) {
			if (!psShowing) {
				psv.show();
				psShowing=true;
			} else if (psShowing) {
				psv.hide();
				psShowing=false;
			}
		}
	}
	public void viewLaneChosen(){
		if ( lane.isPartyAssigned() ) {
			if (!laneShowing) {
				lv.show();
				laneShowing=true;
			} else {
				lv.hide();
				laneShowing=false;
			}
		}
	}
	public void maintenanceChosen(){
		if ( lane.isPartyAssigned() && isPlay ) {
			lane.unPauseGame();
			isMaintained = false;
			maintenance.setBackground( Color.GREEN );
		}
	}
	public void actionPerformed( ActionEvent e ) {
		if (lane.isPartyAssigned() ) {
			ifLaneAssigned(e);
		}
		if (e.getSource().equals(viewLane)) {
			viewLaneChosen();
		}
		if (e.getSource().equals(maintenance)) {
			maintenanceChosen();
		}
		if (e.getSource().equals(play)){
			isPlay = !isPlay;
			if(isPlay){
				if(!isMaintained){lane.unPauseGame();}
				play.setBackground(Color.GREEN);
				return;
			}
			lane.pauseGame();
			play.setBackground(Color.RED);
		}
	}		Insets buttonMargin = new Insets(4, 4, 4, 4);


	public void receiveLaneEvent(LaneEvent le) {
		curBowler.setText( ( (Bowler)le.getBowler()).getNickName() );
		if ( le.isMechanicalProblem() && isPlay) {
			isMaintained = true;
			maintenance.setBackground( Color.RED );
		}	
		if (!lane.isPartyAssigned()) {
			viewLane.setEnabled( false );
			viewPinSetter.setEnabled( false );
		} else {
			viewLane.setEnabled( true );
			viewPinSetter.setEnabled( true );
		}
	}

	public void receivePinsetterEvent(PinsetterEvent pe) {
		pinsDown.setText( (Integer.valueOf(pe.totalPinsDown())).toString() );
	}

}
