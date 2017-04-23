import React from 'react';
import SocialGroup from 'material-ui/svg-icons/social/group'
import {Toolbar, ToolbarTitle} from 'material-ui/Toolbar'
import IconButton from 'material-ui/IconButton'
const TopBar = (props) => {
  const iconStyles = {
      height: 50,
      width: 50,
      marginTop: -10
    },
    onIconClicked = () => {
      props.viewDialog(); // notify the parent
    }
  return (
    <Toolbar style={{backgroundColor: '#9C27B0', color: 'white', marginBottom:20}}>
      <ToolbarTitle text='Free Chat'/>
      <IconButton tooltip=""
                  tooltipPosition="bottom-left"
                  onClick={onIconClicked}
                  iconStyle={iconStyles}
      >
        <SocialGroup style={iconStyles} color='white' />
      </IconButton>
    </Toolbar>
  )
}
export default TopBar
