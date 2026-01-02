import React from 'react';

class Apps extends React.Component {
getText() {
    return "<p>текст</р>";
}
render() {
const text = this.getText();
    return (
        <div>
            {text}
        </div>
    );
  }
}
     
export default Apps;