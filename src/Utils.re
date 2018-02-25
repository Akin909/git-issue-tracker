let textEl = ReasonReact.stringToElement;

let parseRepoJson = (json: Json) => {
Json.Decode.{
  full_name: field("full_name", string, json),
  stargazers_count: field("stargazers_count", int, json),
  html_url: field("html_url", string, json),
};
};
