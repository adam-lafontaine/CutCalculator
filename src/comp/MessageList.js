import React from 'react'
import List from 'material-ui/List/List'
import TextField from 'material-ui/TextField/TextField'
import RaisedButton from 'material-ui/RaisedButton/RaisedButton'
import {Card, CardText} from 'material-ui/Card'
import MessageLeft from './MessageLeft'
import MessageRight from './MessageRight'
import Notification from './Notification'
import styles from '../index.scss'

class MessageList extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      message: '',
      buttonDisabled: true,
      messageList: [],
      notifyList: [],
      txtMessage: null
    };

    this.handleChange = this.handleChange.bind(this);
    this.handleClick = this.handleClick.bind(this);
  }

  componentDidMount() {

    var socket = this.props.socket
    var this_name = this.props.name

    socket.on('server-message', (params) => {
      let messages = this.state.messageList

      if(params.name === this_name){
        messages.push(<MessageLeft name={params.name} time={params.time} text={params.message} color={params.color}/>)
      }
      else if(params.user_joined && params.user_joined === this_name){
        messages.push(<MessageRight name={params.name} time={params.time} text={params.welcome_message} color={params.color}/>)
      }
      else{
        messages.push(<MessageRight name={params.name} time={params.time} text={params.message} color={params.color}/>)
      }
      this.setState({messageList: messages})

      let notifications = this.state.notifyList
      this.setState({notifyList: notifications.filter((item => item.key != params.name))})
    });

    socket.on('user-typing', (params) => {
      let notifications = this.state.notifyList
      let textColor = params.color
      let name = params.name

      if(name !== this_name){
        let msg = `${name} is typing...`
        notifications.unshift(<Notification key={name} color={textColor} text={msg} />)
        this.setState({notifyList: notifications})
      }
    })

    socket.on('user-not-typing', (params) => {
      let notifications = this.state.notifyList
      this.setState({notifyList: notifications.filter((item => item.key != params.name))})
    })
  }

  handleChange(event) {
    if(!this.state.txtMessage)
      this.setState({txtMessage: event.target})

    let msg = event.target.value

    if(msg.length === 1 && this.state.message.length === 0){
      this.props.socket.emit('notify-typing')
    }

    if(msg.length === 0){
      this.props.socket.emit('notify-not-typing')
    }

    this.setState({message: msg});
    this.setState({buttonDisabled: msg.length === 0})
  }

  handleClick() {
    this.state.txtMessage.value = ""
    this.props.socket.emit('chat-message', this.state.message)
    this.setState({message: ""})
  }


  render() {

    return (
      <div>
        <div className={styles.notificationList}>
          <List>{this.state.notifyList}</List>
        </div>
        <Card>
          <CardText style={{textAlign: 'center'}}>
            <div className={styles.messageList}>
              <List>{this.state.messageList}</List>
            </div>
          </CardText>
        </Card>
        <div className={styles.messageInput}>
          <TextField
            onChange={this.handleChange}
            placeholder="Enter Message"
          />
          <RaisedButton
            label="Send"
            backgroundColor="#43A047"
            onTouchTap={this.handleClick}
          />
        </div>
      </div>
    );
  }
}
export default MessageList
