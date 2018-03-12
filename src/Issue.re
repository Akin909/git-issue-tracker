open Utils;

type state = {show: bool};

type action =
  | Click;

let component = ReasonReact.reducerComponent("Issue");

let make = (~issue, _children) => {
  ...component,
  initialState: () => {show: true},
  reducer: (action, state) =>
    switch (action) {
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
      <div className="issue__label__container">
        (
          Array.map(
            label =>
              <div
                key=label.name
                className="issue__label"
                style=(style(~backgroundColor="#" ++ label.color, ()))>
                (textEl(String.capitalize(label.name)))
              </div>,
            issue.labels
          )
          |> ReasonReact.arrayToElement
        )
      </div>
      <div className="issue__content__container">
        <div
          className="issue__content__text"
          dangerouslySetInnerHTML=(
            dangerousHtml(state.show ? marked(issue.body) : "")
          )
        />
        <section className="issue__content__sidebar">
          <figure>
            <img
              src=issue.user.avatar_url
              alt="user profile"
              className="image image--github image--relative"
            />
            <figcaption className="issue__username">
              (textEl(issue.user.login))
            </figcaption>
          </figure>
          <button className="button button--small">
            (textEl("Comments"))
          </button>
          <button
            className="button button--small" onClick=(_evt => send(Click))>
            (textEl(state.show ? "Collapse" : "Expand"))
          </button>
        </section>
      </div>
    </li>
};
