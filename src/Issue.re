open Utils;

type state = {show: bool};

type action =
  | Click;

let component = ReasonReact.reducerComponent("Issue");

let make = (~issue, _children) => {
  ...component,
  initialState: () => {show: false},
  reducer: (action, state) =>
    switch action {
    | Click => ReasonReact.Update({show: ! state.show})
    },
  render: ({send, state}) =>
    <li className="issue__container">
      <h2 className="issue__title">
        (textEl(issue.title))
        <span className="issue__number">
          (textEl("#" ++ string_of_int(issue.number)))
        </span>
      </h2>
      <div className="issue__content__container" onClick=(_evt => send(Click))>
        <p className="issue__content__text">
          (state.show ? textEl(issue.body) : ReasonReact.nullElement)
        </p>
        <button className="button button-small">
          (textEl(state.show ? "Collapse" : "Expand"))
        </button>
      </div>
    </li>
};
