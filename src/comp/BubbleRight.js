import React from 'react'
import styles from '../index.scss'
const BubbleRight = (props) => {
  return (
    <div className={styles.messageBubbleRight} style={{backgroundColor: props.color, color:'white'}}>
      <span className={styles.bubbleLabel}>{props.name} - {props.time}</span><br />
      <span className={styles.bubbleText}>{props.text}</span>
    </div>
  )
}
export default BubbleRight
