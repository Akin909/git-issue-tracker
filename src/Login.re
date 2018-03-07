open Utils;

let component = ReasonReact.statelessComponent("Login");

let clientId = "6a1d3c88efe918d9ade0";

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <a
        className="auth__button"
        href=(
          "https://github.com/login/oauth/authorize?scope=user:email&client_id="
          ++ clientId
        )>
        (textEl("Click here to authenticate your account"))
      </a>
    </div>
};
