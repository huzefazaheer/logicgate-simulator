import styles from './toolbar.module.css'

function Toolbar({ coords }) {
  return (
    <div className={styles.toolbar}>
      <div className={styles.menu}>
        <ul>
          <li>AND GATE</li>
          <li>NOT GATE</li>
          <li>OR GATE</li>
        </ul>
      </div>
      <div className={styles.coord}>
        ({coords[0]},{coords[1]})
      </div>
    </div>
  )
}

export default Toolbar
