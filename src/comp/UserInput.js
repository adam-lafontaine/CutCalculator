import React from 'react'
import TextField from 'material-ui/TextField/TextField'
import RaisedButton from 'material-ui/RaisedButton/RaisedButton'
import {Card, CardActions, CardHeader, CardText} from 'material-ui/Card'
import Divider from 'material-ui/Divider';
import {Table, TableBody, TableHeader, TableHeaderColumn, TableRow, TableRowColumn} from 'material-ui/Table';

class UserInput extends React.Component {
	constructor(props) {
		super(props);
		this.state = {

		};

		this.handleChange = this.handleChange.bind(this);
		this.handleGoClick = this.handleGoClick.bind(this);
	}

	handleChange(event) {
		let name = event.target.value
		this.setState({userName: name});
		this.setState({buttonDisabled: name.length == 0})
	}

	handleGoClick() {
		//validate
		//get input
		let params = {}
		this.props.onShowResults(params)
	}

	handleResetClick() {
		// clear input, remove rows
	}

	render() {
		return (
			<Card>
				<CardActions>
					<RaisedButton
						label="Go"
						primary={true}
						onTouchTap={this.handleGoClick}
					/>
					<RaisedButton
						label="Reset"
						primary={true}
						onTouchTap={this.handleResetClick}
					/>
				</CardActions>
				<Divider />
				<CardHeader
					title="Lengths Needed"
				/>
				<Table
					selectable={false}
				>
					<TableHeader
						displaySelectAll={false}
						adjustForCheckbox={false}
					>
						<TableRow>
							<TableHeaderColumn>ID</TableHeaderColumn>
							<TableHeaderColumn>Name</TableHeaderColumn>
							<TableHeaderColumn>Status</TableHeaderColumn>
						</TableRow>
					</TableHeader>
					<TableBody
						displayRowCheckbox={false}

					>
						<TableRow>
							<TableRowColumn>1</TableRowColumn>
							<TableRowColumn>John Smith</TableRowColumn>
							<TableRowColumn>Employed</TableRowColumn>
						</TableRow>
						<TableRow>
							<TableRowColumn>2</TableRowColumn>
							<TableRowColumn>Randal White</TableRowColumn>
							<TableRowColumn>Unemployed</TableRowColumn>
						</TableRow>
						<TableRow>
							<TableRowColumn>3</TableRowColumn>
							<TableRowColumn>Stephanie Sanders</TableRowColumn>
							<TableRowColumn>Employed</TableRowColumn>
						</TableRow>
						<TableRow>
							<TableRowColumn>4</TableRowColumn>
							<TableRowColumn>Steve Brown</TableRowColumn>
							<TableRowColumn>Employed</TableRowColumn>
						</TableRow>
					</TableBody>
				</Table>
			</Card>
		);
	}
}
export  default UserInput
