open Utils;

let component = ReasonReact.statelessComponent("Home");

module Title = {
  let component = ReasonReact.statelessComponent("Title");
  let make = (~text: string, _children) => {
    ...component,
    render: _self => <h1 className="title"> (textEl(text)) </h1>
  };
};

let make = _children => {
  ...component,
  render: _self =>
    <div className="container">
      <Title text="Git Issue Tracker" />
      <Issues />
    </div>
};
