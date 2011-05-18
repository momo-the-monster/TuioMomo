/*
 TuioPad http://www.tuio.org/
 An Open Source TUIO App for iOS based on OpenFrameworks
 (c) 2010 by Mehmet Akten <memo@memo.tv> and Martin Kaltenbrunner <modin@yuri.at>
 
 TuioPad is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TuioPad is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TuioPad.  If not, see <http://www.gnu.org/licenses/>.
*/

#import "MSAViewController.h"
#import <QuartzCore/CoreAnimation.h>

#import "MSATuioSenderCPP.h"
#import "MSASettings.h"

@implementation MSAViewController

@synthesize settings;
@synthesize tuioSender;
@synthesize isOn;
@synthesize deviceOrientation;
@synthesize chosenGui;


#pragma mark ----- Utility -----

-(void)connect {
	NSLog(@"MSAViewController::connect %@ %@ %i", hostTextField.text, portTextField.text, packetSwitch.selectedSegmentIndex);
	tuioSender->setup([hostTextField.text UTF8String], [portTextField.text intValue], packetSwitch.selectedSegmentIndex, [[settings getIpAddress] UTF8String]);
	
	if(periodicUpdatesSwitch.on) tuioSender->tuioServer->enablePeriodicMessages();
	else tuioSender->tuioServer->disablePeriodicMessages();
	
	if(fullUpdatesSwitch.on) tuioSender->tuioServer->enableFullUpdate();
	else tuioSender->tuioServer->disableFullUpdate();


}

-(void)disconnect {
	tuioSender->close();
}


#pragma mark ----- Control events -----

-(IBAction) orientControlChanged:(id)sender {
		
	switch(orientControl.selectedSegmentIndex) {
		case 0:	
			deviceOrientation = [[UIDevice currentDevice] orientation];
			[[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
			[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didRotate:) name:@"UIDeviceOrientationDidChangeNotification" object:nil];
			break;
			
		case 1:
			deviceOrientation = UIDeviceOrientationLandscapeRight;
			[[NSNotificationCenter defaultCenter] removeObserver:self];
			break;
			
		case 2:
			deviceOrientation = UIDeviceOrientationPortrait;
			[[NSNotificationCenter defaultCenter] removeObserver:self];
			break;
	}
}


-(IBAction) textFieldDoneEditing:(id)sender {
	[sender resignFirstResponder];
}


-(IBAction) backgroundPressed:(id)sender {
	[hostTextField resignFirstResponder];
	[portTextField resignFirstResponder];
}


-(IBAction) connectPressed:(id)sender {
	
	if (!network) return;
	
	[settings setInt:packetSwitch.selectedSegmentIndex forKey:kSetting_Packet];
	if (packetSwitch.selectedSegmentIndex<2) [settings setString:hostTextField.text forKey:kSetting_HostIP];
	[settings setInt:[portTextField.text intValue] forKey:kSetting_Port];
	[settings setInt:orientControl.selectedSegmentIndex forKey:kSetting_Orientation];
	[settings setInt:periodicUpdatesSwitch.on forKey:kSetting_PeriodicUpdates];
	[settings setInt:fullUpdatesSwitch.on forKey:kSetting_FullUpdates];
	[settings saveSettings];
	
	[self close];
	[self connect];
	
}

-(IBAction) freePlayPressed:(id)sender {
	[self close];
}


-(IBAction) packetSelected:(id)sender {
	if (packetSwitch.selectedSegmentIndex==2) {
		NSLog(@"MSAViewController::set %@", hostTextField.text);
		[settings setString:hostTextField.text forKey:kSetting_HostIP];
		hostTextField.text = @"incoming connection";
		hostTextField.textColor = [UIColor grayColor];
		//hostLabel.text = @"server";
		hostTextField.enabled = NO;
		hostButton.enabled = NO;
	} else {
		hostTextField.text = [settings getString:kSetting_HostIP];
		hostTextField.enabled = YES;
		hostButton.enabled = YES;
		hostTextField.textColor = [UIColor blackColor];
		//hostLabel.text = @"client";
	}
}



-(IBAction) detectHostPressed:(id)sender {
	if (packetSwitch.selectedSegmentIndex<2)
		hostTextField.text = [settings getDefaultFor:kSetting_HostIP];
}


-(IBAction) defaultPortPressed:(id)sender {
	packetSwitch.selectedSegmentIndex = 0;
	portTextField.text = [NSString stringWithFormat:@"%i", [[settings getDefaultFor:kSetting_Port] intValue]];
}



#pragma mark ----- Open & close -----

#define ANIMATION_TIME		0.5f
#define ANIMATION_CURVE		UIViewAnimationCurveEaseIn

-(void)open:(bool)animate {
	NSLog(@"MSAViewController::open %i", animate);
		
	if(self.view.superview == nil) {
		if(animate) {
			[UIView beginAnimations:nil context:NULL];
			[UIView setAnimationDuration:ANIMATION_TIME];
			[UIView setAnimationTransition:UIViewAnimationTransitionFlipFromRight forView:[[UIApplication sharedApplication] keyWindow] cache:YES];
			[UIView setAnimationCurve: ANIMATION_CURVE];
			[self viewWillAppear:YES];
			[[[UIApplication sharedApplication] keyWindow] addSubview:self.view];
			[self viewDidAppear:YES];
			[UIView commitAnimations];
		} else {
			[[[UIApplication sharedApplication] keyWindow] addSubview:self.view];
		}
		
			}
	
	// suspend update loop while UI is visible
	isOn = true;
	[self disconnect];
	ofSetFrameRate(1);			
}


-(void) close {
	NSLog(@"MSAViewController::close");
	
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDuration:ANIMATION_TIME];
	[UIView setAnimationTransition:UIViewAnimationTransitionFlipFromLeft forView:[[UIApplication sharedApplication] keyWindow] cache:YES];
	[UIView setAnimationCurve: ANIMATION_CURVE];
	[self viewWillDisappear:YES];
	[self.view removeFromSuperview];
	[self viewDidDisappear:YES];
	[UIView commitAnimations];
	

	ofSetFrameRate(60);			// restore update loop	
	isOn = false;
}

-(IBAction) exitPressed:(id)sender {
	
	[settings setInt:packetSwitch.selectedSegmentIndex forKey:kSetting_Packet];
	if (packetSwitch.selectedSegmentIndex<2) [settings setString:hostTextField.text forKey:kSetting_HostIP];
	[settings setInt:[portTextField.text intValue] forKey:kSetting_Port];
	[settings setInt:orientControl.selectedSegmentIndex forKey:kSetting_Orientation];
	[settings setInt:periodicUpdatesSwitch.on forKey:kSetting_PeriodicUpdates];
	[settings setInt:fullUpdatesSwitch.on forKey:kSetting_FullUpdates];
	[settings saveSettings];	
	exit(0);
}


#pragma mark ----- Default events -----

-(void)viewDidLoad {
	NSLog(@"MSAViewController::viewDidLoad");
	[super viewDidLoad];
	
	[UIView setAnimationBeginsFromCurrentState:YES];
	
	
	tuioSender = new MSATuioSenderCPP();
	
	NSString *HostIP = [settings getString:kSetting_HostIP];
	packetSwitch.selectedSegmentIndex		= [settings getInt:kSetting_Packet];
	if (packetSwitch.selectedSegmentIndex<2)
		hostTextField.text					= [settings getString:kSetting_HostIP];	
	else {
		hostTextField.text = @"incoming connection";
		hostTextField.textColor = [UIColor grayColor];
		hostTextField.enabled = NO;
		hostButton.enabled = NO;
	}
	[settings setString:HostIP forKey:kSetting_HostIP];
	portTextField.text						= [NSString stringWithFormat:@"%i", [settings getInt:kSetting_Port]];
	orientControl.selectedSegmentIndex		= [settings getInt:kSetting_Orientation];
	periodicUpdatesSwitch.on				= [settings getInt:kSetting_PeriodicUpdates];
	fullUpdatesSwitch.on					= [settings getInt:kSetting_FullUpdates];
	
	[self.navigationController pushViewController:self animated:YES];
	
	[self orientControlChanged:nil];
	
	network = [settings connectedToNetwork];
	if (network) {
		NSString *address = [settings getIpAddress];
		
		NSString *status = [NSString stringWithFormat:@"current network address is %@", address];
		statusLabel.textColor = [UIColor whiteColor];
		statusLabel.text = status;
		[startButton setEnabled: YES];
		NSLog([NSString stringWithFormat:@"MSAViewController: %@", status]);
	} else {
		statusLabel.textColor = [UIColor redColor];
		statusLabel.text = @"no active network connection available!";
		[startButton setEnabled: NO];
		//NSLog(@"MSAViewController: no active network connection available!");
	}
	
//	[self connect];
	
	visualsArray = [[NSArray alloc] initWithObjects:@"FingerDrawer",@"FiddlyBits", nil];
	
	// set and scroll the Visualizer table
	NSUInteger selectedRow[] = {0, [settings getInt:kSetting_GuiRowIndex]};
	NSIndexPath *selIndexPath = [NSIndexPath indexPathWithIndexes:selectedRow length:2];
	[tblSimpleTable selectRowAtIndexPath:selIndexPath animated:false scrollPosition:UITableViewScrollPositionTop];
	chosenGui = [settings getInt:kSetting_GuiRowIndex];

}



- (void) didRotate:(NSNotification *)notification {	
	int o = [[UIDevice currentDevice] orientation];
	if(o != UIDeviceOrientationUnknown && o != UIDeviceOrientationFaceUp && o != UIDeviceOrientationFaceDown) {
		deviceOrientation = o;
	} else if([settings getInt:kSetting_Orientation] == 0) {
		deviceOrientation = UIDeviceOrientationLandscapeRight;
	}
}




- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void)didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
}


- (void)dealloc {
	delete tuioSender;
    [super dealloc];
}

#pragma mark Table view methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return 1;
}

// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
	NSInteger numObjects = [visualsArray count];
	return numObjects;
}

- (NSString*)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
	return @"Visualizer";
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[settings setInt:indexPath.row forKey:kSetting_GuiRowIndex];
	chosenGui = indexPath.row;
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	static NSString *CellIdentifier = @"Cell";
	
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	if (cell == nil) {
		cell = [[[UITableViewCell alloc] initWithFrame:CGRectZero reuseIdentifier:CellIdentifier] autorelease];
	}
	
	// Set up the cell...
	cell.text = [visualsArray objectAtIndex:indexPath.row];
	return cell;
}

@end
