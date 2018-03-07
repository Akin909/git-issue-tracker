open Utils;

type action =
  | ReposFetched(repo)
  | URLChanged(string)
  | FetchRepos(string)
  | ReposFetchFailed(string);

type state =
  | Loading
  | Loaded(repo)
  | Error(string)
  | Authenticated(string);

let component = ReasonReact.reducerComponent("Home");

let defaultHeaders = [%bs.raw {|
{
  username: "Akin909",
}
|}];

let headers = Fetch.HeadersInit.make(defaultHeaders);

let make = _children => {
  ...component,
  initialState: () => Loading,
  subscriptions: (self) => [
    Sub(() => ReasonReact.Router.watchUrl(
        url => {
          switch (url.hash, url.path){
            | (hash, _path) => self.send(URLChanged(hash))
            }
        }
    ),
      ReasonReact.Router.unwatchUrl
    )
  ],
  reducer: (action, _state) =>
    switch action {
    | FetchRepos(_code) =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.
              (
                Fetch.fetch("https://api.github.com/onivim/oni")
                |> then_(Fetch.Response.json)
                |> then_(json =>
                     json
                     |> parseRepoJson
                     |> (repo => self.send(ReposFetched(repo)))
                     |> resolve
                   )
                |> catch(err => {
                  Js.log(err);
                  Js.Promise.resolve(
                    self.send(
                      ReposFetchFailed(
                        "Sorry I was unable to get the repo data"
                      )
                    )
                  );
                  }
                   )
                |> ignore
              )
        )
      )
    | ReposFetched(repo) => ReasonReact.Update(Loaded(repo))
    | ReposFetchFailed(error) => ReasonReact.Update(Error(error))
    | URLChanged(code) => ReasonReact.Update(Authenticated(code))
    },
  didMount: self => {
    let url = ReasonReact.Router.dangerouslyGetInitialUrl();
    let code = Js.String.split("=", url.search)[1];
    self.send(FetchRepos(code));
    ReasonReact.NoUpdate;
  },
  render: ({ state }) => {
    <div className="main__content">
    {
      switch state {
        | Loading => <div> (textEl("Loading...")) </div>
        | Error(error) => <div className="error"> (textEl(error)) </div>
        | Loaded(repo) => <Tile repo />
        | Authenticated(code) => <div>(textEl(code))</div>
        }
    }
    </div>
  }
};
