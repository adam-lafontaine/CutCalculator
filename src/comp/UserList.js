import React from 'react'
import List from 'material-ui/List/List'
import User from './User'
const UserList = (props) => {
  const users = props.users.map((user) => {
    return (<User name={user.name} color={user.color}/>);
  })
  return (
    <List>
      {users}
    </List>
  )
}
export default UserList
