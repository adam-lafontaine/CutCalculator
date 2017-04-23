import React from 'react'
import TextField from 'material-ui/TextField/TextField'
import RaisedButton from 'material-ui/RaisedButton/RaisedButton'
import {Card, CardText} from 'material-ui/Card'

class SignIn extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      userName: '',
      buttonDisabled: true
    };

    this.handleChange = this.handleChange.bind(this);
    this.handleClick = this.handleClick.bind(this);
  }

  handleChange(event) {
    let name = event.target.value
    this.setState({userName: name});
    this.setState({buttonDisabled: name.length == 0})
  }

  handleClick() {
    let params = {}
    params.name = this.state.userName

    this.props.onSignIn(params)
  }

  render() {
    return (
      <Card style={{textAlign: 'center'}}>
        <CardText>
          <TextField
            onChange={this.handleChange}
            placeholder="Chat Name"
            hintText="Chat Name"
            errorText={this.props.error}
          /><br/>
          <RaisedButton
            label="Join Chat"
            backgroundColor="#03A9F4"
            onTouchTap={this.handleClick}
            disabled={this.state.buttonDisabled}
          />
        </CardText>
      </Card>
    );
  }
}
export  default SignIn
